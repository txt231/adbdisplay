//---------------------------------------------------------------------------
//
//	   Copyright (C) 2017 bbraun
//	   Copyright (C) 2021-2022 akuker
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
//---------------------------------------------------------------------------
#pragma once

#include <avr/io.h>
#include <util/delay.h>
#include <avr/cpufunc.h>
#include <LibPrintf.h>

#define adb_delay_us(x) _delay_us(x)
#define adb_delay_ms(x) _delay_ms(x)

class AdbInterfacePlatform 
{
public:
	void Init()
	{ 
		adb_pin_in(); 
	}

protected:
	// These need to be looked upon the arduino schematic to figure out
	// which bank and databit the ADB pin is connected to
	// Default is PIN 8 (i had issues with PIN 3)
	#define ADB_PORT      PORTB
	#define ADB_PIN       PINB
	#define ADB_DDR       DDRB
	#define ADB_DATA_BIT  0
	
	inline void data_lo();
	inline void data_hi();
	inline void adb_pin_out();
	inline void adb_pin_in();
	inline uint8_t data_in();

	inline uint16_t wait_data_lo(uint32_t us);
	inline uint16_t wait_data_hi(uint32_t us);
	
	// bool adb_delay_us(double delay);
};


inline void AdbInterfacePlatform::data_lo()
{
	// output
	(ADB_DDR |= (1 << ADB_DATA_BIT));
	
	// drive low
	(ADB_PORT &= ~(1 << ADB_DATA_BIT));
}

inline void AdbInterfacePlatform::data_hi()
{
	// input 
	(ADB_DDR &= ~(1 << ADB_DATA_BIT));
}
inline uint8_t AdbInterfacePlatform::data_in()
{
	return (ADB_PIN & (1 << ADB_DATA_BIT));
}

inline void AdbInterfacePlatform::adb_pin_out()
{
	(ADB_DDR |= (1 << ADB_DATA_BIT));
}
inline void AdbInterfacePlatform::adb_pin_in()
{
	(ADB_DDR &= ~(1 << ADB_DATA_BIT));
}

inline uint16_t AdbInterfacePlatform::wait_data_lo(uint32_t us)
{
    do {
        if ( !data_in() )
            break;
        _delay_us(1 - (6 * 1000000.0 / F_CPU));
    }
    while ( --us );
    return us;

//   uint32_t timer = 0;
//   do
//   {
//     if (!data_in())
//       break;
//     _delay_us(1 - (12 * 1000000.0 / F_CPU));
//     _NOP();
//     timer++;
//   } while (us > timer);
//   return timer;
}

inline uint16_t AdbInterfacePlatform::wait_data_hi(uint32_t us)
{

    do {
        if ( data_in() )
            break;
        _delay_us(1 - (6 * 1000000.0 / F_CPU));
    }
    while ( --us );
    return us;

//   uint32_t timer = 0;
//   do
//   {
//     if (data_in())
//       break;
//     _delay_us(1 - (12 * 1000000.0 / F_CPU));
//     _NOP();
//     timer++;
//   } while (us > timer);
//   return timer;
}

// inline bool AdbInterfacePlatform::adb_delay_us(double delay)
// {
//     // for this _delay_us to compile "__DELAY_BACKWARD_COMPATIBLE__" 
//     // must be defined in the platformio.ini file. Otherwise
//     // it can only be delayed with compile time computations
    
//     // there seems to be a compiling issue. For some reason the if
//     // statement fixes the issue.
// 	_delay_us(delay);  
//     return true; 
// }