/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2010 Gareth McMullin <gareth@blacksphere.co.nz>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */
/*
 * Significant parts of this originated from
 * libopencm3-examples/examples/stm32/f4/stm32f429i-discovery/usb_cdcacm 
 * which is why I left the copyright notice above. 
 * current: https://github.com/dhylands/libopencm3-usb-serial/blob/master/usb.c
 */

#include "usb.h"

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/cdc.h>
#include <libopencm3/usb/dwc/otg_fs.h>
#include <libopencm3/stm32/desig.h>


template <uint16_t Count=1024>
class Buf
{
protected:
	uint8_t m_Data[Count]; 
	volatile uint16_t m_get_idx;
	volatile uint16_t m_put_idx;
	
	inline uint16_t Mask()
	{
		return Count-1; // mask for count, has to be a power of 2?
	}
	
	inline bool Wrapped()
	{
		// check if put and get xored toget is over mask
		return (((m_put_idx ^ m_get_idx) & ~Mask()) != 0);
	}

public:
	inline uint16_t Len()
	{
		return m_put_idx - m_get_idx;
	}
	inline uint16_t Space()
	{
		return Count - Len();
	}
	inline bool Empty()
	{
		return Len() == 0;
	}
	inline bool Full()
	{
		return Space() == 0;
	}

	uint16_t ContigLen()
	{
		return (Wrapped() ? (Count - (m_get_idx & Mask())) 	: Len());
	}
	uint16_t ContigSpace()
	{
		return (Wrapped() ? Space() 						: (Count - (m_put_idx & Mask())));
	}

	void PushSkip(uint16_t len)
	{
		m_put_idx += len;
	}
	bool Push(uint8_t val)
	{
		if (Space() == 0)
			return false;

		m_Data[m_put_idx++ & Mask()] = val;
		return true;
	}

	void PopSkip(uint16_t len)
	{
		m_get_idx += len;
	}
	uint8_t Pop()
	{
		return m_Data[m_get_idx++ & Mask()];
	}

	uint8_t* PushPtr()
	{
		return m_Data + (m_put_idx & Mask());
	}
	uint8_t* PopPtr()
	{
		return m_Data + (m_get_idx & Mask());
	}
};
;

static Buf<>	usb_serial_rx_buf;
static Buf<>	usb_serial_tx_buf;
static bool   	usb_serial_need_empty_tx = false;

static usbd_device *g_usbd_dev = NULL;
static volatile bool g_usbd_is_connected = false; 

static char usb_serial[13];	// 12 digits plus a null terminator

// Use a scheme similar to MicroPython, but offset the PIDs by 0x100
// VID: 0xf055
// PID: 0x9900 CDC + MSC (which I have no plans on supporting)
//		0x9901 CDC + HID
//		0x9902 CDC only

static const struct usb_device_descriptor dev = {
	.bLength = USB_DT_DEVICE_SIZE,
	.bDescriptorType = USB_DT_DEVICE,
	.bcdUSB = 0x0200,
	.bDeviceClass = USB_CLASS_CDC,
	.bDeviceSubClass = 0,
	.bDeviceProtocol = 0,
	.bMaxPacketSize0 = 64,
	.idVendor = 0x0483,		// VID
	.idProduct = 0x5740,	// PID
	.bcdDevice = 0x0200,	// Version (2.00)
	.iManufacturer = 1,
	.iProduct = 2,
	.iSerialNumber = 3,
	.bNumConfigurations = 1,
};

/*
 * This notification endpoint isn't implemented. According to CDC spec it's
 * optional, but its absence causes a NULL pointer dereference in the
 * Linux cdc_acm driver.
 */
static const struct usb_endpoint_descriptor comm_endp[] = {{
	.bLength = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,
	.bEndpointAddress = 0x83,
	.bmAttributes = USB_ENDPOINT_ATTR_INTERRUPT,
	.wMaxPacketSize = 16,
	.bInterval = 255,
} };

static const struct usb_endpoint_descriptor data_endp[] = {
	{
		.bLength = USB_DT_ENDPOINT_SIZE,
		.bDescriptorType = USB_DT_ENDPOINT,
		.bEndpointAddress = 0x01,
		.bmAttributes = USB_ENDPOINT_ATTR_BULK,
		.wMaxPacketSize = 64,
		.bInterval = 0,
	}, 
	{
		.bLength = USB_DT_ENDPOINT_SIZE,
		.bDescriptorType = USB_DT_ENDPOINT,
		.bEndpointAddress = 0x82,
		.bmAttributes = USB_ENDPOINT_ATTR_BULK,
		.wMaxPacketSize = 64,
		.bInterval = 0,
	} 
};

static const struct {
	struct usb_cdc_header_descriptor header;
	struct usb_cdc_call_management_descriptor call_mgmt;
	struct usb_cdc_acm_descriptor acm;
	struct usb_cdc_union_descriptor cdc_union;
} __attribute__((packed)) cdcacm_functional_descriptors = {
	.header = {
		.bFunctionLength = sizeof(struct usb_cdc_header_descriptor),
		.bDescriptorType = CS_INTERFACE,
		.bDescriptorSubtype = USB_CDC_TYPE_HEADER,
		.bcdCDC = 0x0110,
	},
	.call_mgmt = {
		.bFunctionLength =
			sizeof(struct usb_cdc_call_management_descriptor),
		.bDescriptorType = CS_INTERFACE,
		.bDescriptorSubtype = USB_CDC_TYPE_CALL_MANAGEMENT,
		.bmCapabilities = 0,
		.bDataInterface = 1,
	},
	.acm = {
		.bFunctionLength = sizeof(struct usb_cdc_acm_descriptor),
		.bDescriptorType = CS_INTERFACE,
		.bDescriptorSubtype = USB_CDC_TYPE_ACM,
		.bmCapabilities = 0x2, //TODO: check change
	},
	.cdc_union = {
		.bFunctionLength = sizeof(struct usb_cdc_union_descriptor),
		.bDescriptorType = CS_INTERFACE,
		.bDescriptorSubtype = USB_CDC_TYPE_UNION,
		.bControlInterface = 0,
		.bSubordinateInterface0 = 1,
	 }
};

static const struct usb_interface_descriptor comm_iface[] = {{
	.bLength = USB_DT_INTERFACE_SIZE,
	.bDescriptorType = USB_DT_INTERFACE,
	.bInterfaceNumber = 0,
	.bAlternateSetting = 0,
	.bNumEndpoints = 1,
	.bInterfaceClass = USB_CLASS_CDC,
	.bInterfaceSubClass = USB_CDC_SUBCLASS_ACM,
	.bInterfaceProtocol = USB_CDC_PROTOCOL_AT,
	.iInterface = 0,

	.endpoint = comm_endp,

	.extra = &cdcacm_functional_descriptors,
	.extralen = sizeof(cdcacm_functional_descriptors)
} };

static const struct usb_interface_descriptor data_iface[] = {{
	.bLength = USB_DT_INTERFACE_SIZE,
	.bDescriptorType = USB_DT_INTERFACE,
	.bInterfaceNumber = 1,
	.bAlternateSetting = 0,
	.bNumEndpoints = 2,
	.bInterfaceClass = USB_CLASS_DATA,
	.bInterfaceSubClass = 0,
	.bInterfaceProtocol = 0,
	.iInterface = 0,

	.endpoint = data_endp,
} };

static const struct usb_interface ifaces[] = {
	{
		.cur_altsetting = nullptr,
		.num_altsetting = 1,
		.iface_assoc = nullptr,
		.altsetting = comm_iface,
	},
	{
		.cur_altsetting = nullptr,
		.num_altsetting = 1,
		.iface_assoc = nullptr,
		.altsetting = data_iface,
	} 
};

static const struct usb_config_descriptor config = {
	.bLength = USB_DT_CONFIGURATION_SIZE,
	.bDescriptorType = USB_DT_CONFIGURATION,
	.wTotalLength = 0,
	.bNumInterfaces = 2,
	.bConfigurationValue = 1,
	.iConfiguration = 0,
	.bmAttributes = 0x80,
	//.bMaxPower = 0x32,
	.bMaxPower = 250,	// units of 2mA

	.interface = ifaces,
};

static const char *usb_strings[] = {
	"Manufacturer",
	"STM32F4 CDC Demo",
	usb_serial,
};
#define NUM_USB_STRINGS (sizeof(usb_strings) / sizeof(usb_strings[0]))

static const struct usb_cdc_line_coding line_coding = {
	.dwDTERate = 115200,
	.bCharFormat = USB_CDC_1_STOP_BITS,
	.bParityType = USB_CDC_NO_PARITY,
	.bDataBits = 0x08
};

/* Buffer to be used for control requests. */
uint8_t usbd_control_buffer[128];

#define USB_CDC_REQ_GET_LINE_CODING			0x21 // Not defined in libopencm3
/*
typedef enum usbd_request_return_codes (*usbd_control_callback)(
		usbd_device *usbd_dev,
		struct usb_setup_data *req, uint8_t **buf, uint16_t *len,
		usbd_control_complete_callback *complete)
*/
static enum usbd_request_return_codes cdcacm_control_request(usbd_device *usbd_dev,
	struct usb_setup_data *req, uint8_t **buf, uint16_t *len,
	usbd_control_complete_callback *complete)
{
	(void)complete;
	(void)buf;
	(void)usbd_dev;

	switch (req->bRequest) 
	{

	case USB_CDC_REQ_SET_CONTROL_LINE_STATE: 
	{	// 0x22
		uint16_t rtsdtr = req->wValue;	// DTR is bit 0, RTS is bit 1
		g_usbd_is_connected = rtsdtr & 1;
		return USBD_REQ_HANDLED;
	}

	case USB_CDC_REQ_SET_LINE_CODING:	// 0x20
	{
		if (*len < sizeof(struct usb_cdc_line_coding)) 
			return USBD_REQ_NOTSUPP;
		struct usb_cdc_line_coding* pCoding = (struct usb_cdc_line_coding*)*buf;
		
		return USBD_REQ_HANDLED;
	}

	case USB_CDC_REQ_GET_LINE_CODING:
		*buf = (uint8_t *)&line_coding;
		return USBD_REQ_HANDLED;
	}
	return USBD_REQ_HANDLED;
}

static void cdcacm_data_rx_cb(usbd_device *usbd_dev, uint8_t ep)
{
	uint16_t space = usb_serial_rx_buf.ContigSpace();
	uint16_t len;
	if (space >= 64) 
	{
		// We can read directly into our buffer
		len = usbd_ep_read_packet(usbd_dev, ep, 
								  usb_serial_rx_buf.PushPtr(), 64);
		usb_serial_rx_buf.PushSkip(len);
	} 
	else
	{
		// Do it character by character. This covers 2 situations:
		// 1 - We're near the end of the buffer (so free space isn't contiguous)
		// 2 - We don't have much free space left.
		char buf[64];
		len = usbd_ep_read_packet(usbd_dev, ep, buf, 64);
		for (int i = 0; i < len; i++) 
		{
			// If the Rx buffer fills, then we drop the new data.
			if(!usb_serial_rx_buf.Push(buf[i]))
				return;
		}
	}
}

static void cdcacm_sof_callback(void) {
	if (!g_usbd_is_connected) {
		// Host isn't connected - nothing to do.
		return;
	}

	uint16_t len = usb_serial_tx_buf.ContigLen();

	// Nothing to do.
	if (len == 0 && !usb_serial_need_empty_tx) 
		return;

	if (len > 64) 
		len = 64;

	uint8_t *pop_ptr = usb_serial_tx_buf.PopPtr();
	uint16_t sent = usbd_ep_write_packet(g_usbd_dev, 0x82, pop_ptr, len);

	// If we just sent a packet of 64 bytes. If we get called again and
	// there is no more data to send, then we need to send a zero byte
	// packet to indicate to the host to release the data it has buffered.
	usb_serial_need_empty_tx = (sent == 64);
	usb_serial_tx_buf.PopSkip(sent);
}

extern "C" void otg_fs_isr(void)
{
	if (g_usbd_dev) 
		usbd_poll(g_usbd_dev);
}

static void cdcacm_set_config(usbd_device *usbd_dev, uint16_t wValue)
{
	(void)wValue;

	usbd_ep_setup(usbd_dev, 0x01, USB_ENDPOINT_ATTR_BULK, 64,
			cdcacm_data_rx_cb);
	usbd_ep_setup(usbd_dev, 0x82, USB_ENDPOINT_ATTR_BULK, 64, NULL);
	usbd_ep_setup(usbd_dev, 0x83, USB_ENDPOINT_ATTR_INTERRUPT, 16, NULL);

	usbd_register_control_callback(
				usbd_dev,
				USB_REQ_TYPE_CLASS | USB_REQ_TYPE_INTERFACE,
				USB_REQ_TYPE_TYPE | USB_REQ_TYPE_RECIPIENT,
				cdcacm_control_request);
}

void usb_vcp_poll(void)
{
	if (g_usbd_dev)
		usbd_poll(g_usbd_dev);
}

bool usb_vcp_is_connected(void) {
	return g_usbd_is_connected;
}

uint16_t usb_vcp_avail(void) {
	return usb_serial_rx_buf.Len();
}

int usb_vcp_recv_byte(void) {
	if (usb_serial_rx_buf.Empty())
		return -1;
	
	return usb_serial_rx_buf.Pop();
}

void usb_vcp_send_byte(uint8_t ch) {
	if (!usb_serial_tx_buf.Full()) 
		usb_serial_tx_buf.Push(ch);
	
}

void usb_vcp_send_strn(const char *str, size_t len) {
	for (const char *end = str + len; str < end; str++)
		usb_vcp_send_byte(*str);
	
}

void usb_vcp_send_strn_cooked(const char *str, size_t len) {
	for (const char *end = str + len; str < end; str++) {
		if (*str == '\n')
			usb_vcp_send_byte('\r');
		
		usb_vcp_send_byte(*str);
	}
}

static int usb_putc(void *out_param, int ch) {
	(void)out_param;
	if (ch == '\n')
		usb_vcp_send_byte('\r');
	
	usb_vcp_send_byte(ch);
	return 1;
}

static void fill_usb_serial(void) {
    // This document: http://www.usb.org/developers/docs/devclass_docs/usbmassbulk_10.pdf
    // says that the serial number has to be at least 12 digits long and that
    // the last 12 digits need to be unique. It also stipulates that the valid
    // character set is that of upper-case hexadecimal digits.
    //
    // The onboard DFU bootloader produces a 12-digit serial number based on
    // the 96-bit unique ID, so for consistency we go with this algorithm.
    // You can see the serial number if you do:
    //
    //     dfu-util -l
    //
    // See: https://my.st.com/52d187b7 for the algorithim used.

	uint8_t *id = (uint8_t *)DESIG_UNIQUE_ID_BASE;

	uint8_t serial[6];
	serial[0] = id[11];
	serial[1] = id[10] + id[2];
	serial[2] = id[9];
	serial[3] = id[8] + id[0];
	serial[4] = id[7];
	serial[5] = id[6];

	uint8_t *ser = &serial[0];
	uint8_t *end = &serial[6];
	char *ser_str = usb_serial;
	const char hex_digit[] = "0123456789ABCDEF";

	for (; ser < end; ser++) 
	{
		*ser_str++ = hex_digit[(*ser >> 4) & 0x0f];
		*ser_str++ = hex_digit[(*ser >> 0) & 0x0f];
	}
	*ser_str = '\0';
}

void usb_vcp_init(void) {
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_OTGFS);

	// A9  - USB VBUS (used to detect cable plugged in)
	// A10 - USB_ID (not currently used)
	// A11 - USB D-
	// A12 - USB D+

	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9 | GPIO11 | GPIO12);
	gpio_set_af(GPIOA, GPIO_AF10, GPIO9 | GPIO10 | GPIO11 | GPIO12);

	fill_usb_serial();

	g_usbd_dev = usbd_init(&otgfs_usb_driver, &dev, &config,
			usb_strings, NUM_USB_STRINGS,
			usbd_control_buffer, sizeof(usbd_control_buffer));
	
	// fix https://github.com/libopencm3/libopencm3/issues/1119
#ifdef STM32F4
	OTG_FS_GCCFG |= OTG_GCCFG_NOVBUSSENS;
	// OTG_FS_GCCFG &= ~OTG_GCCFG_VBUSBSEN;
#endif

	usbd_register_set_config_callback(g_usbd_dev, cdcacm_set_config);
	usbd_register_sof_callback(g_usbd_dev, cdcacm_sof_callback);


	// nvic_set_priority(NVIC_OTG_FS_IRQ, (1 << 4));
	nvic_enable_irq(NVIC_OTG_FS_IRQ);
	// nvic_enable_irq(NVIC_OTG_FS_IRQ);
}