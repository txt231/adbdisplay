#include "platform.h"


void platform_init()
{
	Serial.begin(115200);
	while (!Serial);
}

bool serial_rx_avail()
{
	return Serial.available() > 0;
}
size_t serial_rx_read(uint8_t* pData, size_t len)
{
	size_t Read = 0;
	for (; Read < len && serial_rx_avail(); Read++)
		pData[Read] = Serial.read();
	
	return Read;
}