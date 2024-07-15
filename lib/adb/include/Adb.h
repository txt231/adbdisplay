//---------------------------------------------------------------------------
//
//	   Copyright (C) 2017 bbraun
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
//----------------------------------------------------------------------------
#pragma once

#include <LibPrintf.h>

#include <stdint.h>
#include <AdbPlatform.h>

#include "AdbTypes.h"

#ifndef ADB_ATTENTION_WAIT
#define ADB_ATTENTION_WAIT 800
#endif

// extern volatile bool adb_collision;
// extern volatile bool collision_detection;

struct ScanDeviceInfo
{
	uint8_t addr;
	AdbData<AdbReg3> reg;
};

class AdbInterface 
	: public AdbInterfacePlatform 
{
public:
	int16_t Send(AdbOp op);

	template <typename T>
	inline int16_t Send(AdbOp op, AdbData<T>& data)
	{
		return Send(op, data.raw, data.size());
	}

	// void Reset(void);
	

	uint8_t ScanDevices(ScanDeviceInfo regs[16]);

protected:
	// void DetectCollision(void);
	// void ResetCollision(void);
	
	int16_t Send(AdbOp op, uint8_t* pData, uint8_t len);

private:
	bool attention(void);
	bool place_stop_bit(void);

	bool place_bit0(void);
	bool place_bit1(void);
	bool send_byte(uint8_t data);

	// bool place_bit0_with_detect(void);
	// bool place_bit1_with_detect(void);
	// bool send_byte_with_detect(uint8_t data);
};




