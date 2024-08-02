//---------------------------------------------------------------------------
//
//     Copyright 2011 Jun WAKO <wakojun@gmail.com>
//     Copyright 2013 Shay Green <gblargg@gmail.com>
//	   Copyright (C) 2017 bbraun
//	   Copyright (C) 2020 difegue
//	   Copyright (C) 2021-2022 akuker
//     Copyright (C) 2022 Rabbit Hole Computing LLC
//
//  This file was part of the ADBuino and the QuokkaADB projects. 
//  It has been modified to act as a host instead of a device.
//  Most of the modifications to do that is based of the original tmk_keyboard
//  code.
//
//  This file is free software: you can redistribute it and/or modify it under 
//  the terms of the GNU General Public License as published by the Free 
//  Software Foundation, either version 3 of the License, or (at your option) 
//  any later version.
//
//  This file is distributed in the hope that it will be useful, but WITHOUT ANY 
//  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
//  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more 
//  details.
//
//  You should have received a copy of the GNU General Public License along 
//  with the file. If not, see <https://www.gnu.org/licenses/>.
//
//  Portions of this code were originally released under a Modified BSD 
//  License. See LICENSE in the root of this repository for more info.
//
//----------------------------------------------------------------------------

#include "Adb.h" 

int16_t AdbInterface::Send(AdbOp op)
{
	attention();
	send_byte(op.raw);
	place_stop_bit(); // StopBit(0)
	adb_delay_us(200); // tlt/stop to start
	
	return 0;
}

int16_t AdbInterface::Send(AdbOp op, uint8_t* pData, uint8_t dataLen)
{
	// printf("Sending [0x%2x]\n", op.raw);
	// adb_pin_out();
	switch(op.cmd)
	{
	case Reset:
	case Flush:
		return Send(op);
	
	case Listen:
	{
		Send(op);
		place_bit1(); // StartBit(1)

		for (auto i=0; i < dataLen; i++)
			send_byte(pData[i]);
		
		place_stop_bit(); // StopBit(0)
		return 0;
	}
		
	case Talk:
	{
		attention();
		send_byte(op.raw);
		place_stop_bit(); // StopBit(0)
		
		// TODO: do proper delay checking like adbuino does
		
		if (!wait_data_hi(500)) // Service Request(310us Adjustable Keyboard): just ignored
			return -2;
		
		if (!wait_data_lo(500)) // Tlt/Stop to Start(140-260us) | not error
			return dataLen == 0 ? 0 : -7;
				
		// StartBit(1)
		if (!wait_data_hi(40))
			return -3;
		if (!wait_data_lo(100)) 
			return -4;

		uint8_t bit = 0;
		for (; bit < dataLen*8; bit++)
		{
			// printf("[%i] [%i]\n", bit, bit/8);
			//
			// |<- bit_cell_max(130) ->|
			// |        |<-   lo     ->|
			// |        |       |<-hi->|
			//           _______
			// |        |       |
			// | 130-lo | lo-hi |
			// |________|       |
			//
			auto lo = wait_data_hi(130);
			if (!lo)
				break;
				// return -5; // no more bit or after stop bit

			auto hi = wait_data_lo(lo);
			if (!hi)
				break;
				// return -6; // stop bit extedned by Srq?

			pData[bit/8] <<= 1;
			if ((130 - lo) < (lo - hi)) 
				pData[bit/8] |= 1;
		}
		
		// printf("Bits read [%i] [%i]\n", bit, bit/8);
		return (bit/8) == dataLen ? 0 : -7;
		

	}
	}
	

	return -1;
}


uint8_t AdbInterface::ScanDevices(ScanDeviceInfo regs[16])
{
	uint8_t Count = 0;

	for (uint8_t i =0; i < 16; i++)
	{
		AdbData<AdbReg3> Reg;
		Reg.Zero();

		auto Status = Send(AdbOp(i, Talk, Reg_3), Reg);
		if (Status != 0)
		{
			// printf("[%i] Status = %i\n", i, Status);
			continue;
		}
		
		regs[Count++] = ScanDeviceInfo {
			.addr = i,
			.reg = Reg,
		};
	}
	
	return Count;
}



inline bool AdbInterface::attention(void)
{
	data_lo();
	adb_delay_us(ADB_ATTENTION_WAIT-35);
	// adb_delay_us(800-35);
	return place_bit1();
}
// The original data_lo code would just set the bit as an output
// That works for a host, since the host is doing the pullup on the ADB line,
// but for a device, it won't reliably pull the line low.  We need to actually
// set it.

// Stop bit is just bit 0, but this doesn't wait after the signal goes high
inline bool AdbInterface::place_stop_bit(void)
{
	data_lo();
	adb_delay_us(70);
	data_hi();
	return true;
}

inline bool AdbInterface::place_bit0(void)
{
	data_lo();
	adb_delay_us(65);
	data_hi();
	adb_delay_us(35);
	
	return true;
}

inline bool AdbInterface::place_bit1(void)
{
	data_lo();
	adb_delay_us(35);
	data_hi();
	adb_delay_us(65);
	
	return true;
}
inline bool AdbInterface::send_byte(uint8_t data)
{
	for (int i = 0; i < 8; i++)
	{
		if (data & (0x80 >> i))
			place_bit1();
		else
			place_bit0();
	}
	return true;
}