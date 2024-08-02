#include "platform.h"

#include <libopencm3/cm3/common.h>
#include <libopencm3/cm3/memorymap.h>
#include <libopencm3/cm3/itm.h>

#include "clock.h"
#include "usb.h"

#include <errno.h>
#include <sys/unistd.h> // STDOUT_FILENO, STDERR_FILENO

void platform_init()
{
	clock_init();
	
	usb_vcp_init();

}

bool serial_rx_avail()
{
	return usb_vcp_avail();
}
size_t serial_rx_read(uint8_t* pData, size_t len)
{
	size_t Read = 0;
	for (; Read < len && serial_rx_avail(); Read++)
		pData[Read] = usb_vcp_recv_byte();
	
	return Read;
}

// void trace_send_blocking8(int stimulus_port, char c)
// {
// 	if (!(ITM_TER[0] & (1<<stimulus_port))) {
// 		return;
// 	}
// 	while (!(ITM_STIM8(stimulus_port) & ITM_STIM_FIFOREADY));
// 	ITM_STIM8(stimulus_port) = c;
// }

// https://github.com/libopencm3/libopencm3/blob/master/tests/shared/trace_stdio.c
extern "C" ssize_t _write(int fd, const char *buf, size_t n)
{
	if ((fd != STDOUT_FILENO) && (fd != STDERR_FILENO))
	{
		errno = EBADF;
		return -1;
	}

	for (size_t i = 0; i < n; i++)
	{
		usb_vcp_send_byte(buf[i]);
		// trace_send_blocking8(0, buf[i]);
	}

	// return # of bytes written - as best we can tell
	return n;
}