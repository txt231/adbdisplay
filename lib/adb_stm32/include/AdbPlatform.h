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

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>

#include <platform.h>
#include <clock.h>

#define adb_delay_us(microsecs) clock_delay_us(microsecs)
#define adb_delay_ms(millisecs) clock_delay_ms(millisecs)
// #define adb_delay_us(microsecs)
// #define adb_delay_ms(millisecs)


class AdbInterfacePlatform 
{
public:
	void Init()
	{ 
		rcc_periph_clock_enable(RCC_GPIOB);
		adb_pin_out(); 
	}

protected:
	// These need to be looked upon the arduino schematic to figure out
	// which bank and databit the ADB pin is connected to
	// Default is PIN 8 (i had issues with PIN 3)
	
	// how does stm gpios work? i want on pin 12
	#define ADB_PORT      	GPIOB 
	#define ADB_PIN_ID 		1
	#define ADB_PIN_MASK 	(1 << ADB_PIN_ID) // GPIO12
	
	inline void data_lo();
	inline void data_hi();
	inline uint8_t data_in();
	inline void adb_pin_out();

	inline uint16_t wait_data_lo(uint32_t us);
	inline uint16_t wait_data_hi(uint32_t us);
	
	// bool adb_delay_us(double delay);
};


inline void AdbInterfacePlatform::data_lo()
{
	// (ADB_DDR |= (1 << ADB_DATA_BIT));
	// TODO: ADB_PIN bit id
	// GPIO_MODER(ADB_PORT) = (GPIO_MODER(ADB_PORT) & ~GPIO_MODE_MASK(ADB_PIN_ID)) | GPIO_MODE(ADB_PIN_ID, GPIO_MODE_OUTPUT); 

	// drive low
	// GPIO_OTYPER(ADB_PORT) |= 
	// (ADB_PORT &= ~(1 << ADB_DATA_BIT));
	
	GPIO_BSRR(ADB_PORT) = (ADB_PIN_MASK << 16);
	// gpio_clear(ADB_PORT, ADB_PIN_MASK);
}


inline void AdbInterfacePlatform::data_hi()
{
	// TODO: ADB_PIN bit id
	// GPIO_MODER(ADB_PORT) = (GPIO_MODER(ADB_PORT) & ~GPIO_MODE_MASK(ADB_PIN_ID)) | GPIO_MODE(ADB_PIN_ID, GPIO_MODE_OUTPUT); 
	
	// drive data high
	// (ADB_DDR &= ~(1 << ADB_DATA_BIT));

	GPIO_BSRR(ADB_PORT) = ADB_PIN_MASK;
	// gpio_set(ADB_PORT, ADB_PIN_MASK);
}
inline uint8_t AdbInterfacePlatform::data_in()
{
	// return gpio_get(ADB_PORT, ADB_PIN_MASK);
	return (GPIO_IDR(ADB_PORT) & ADB_PIN_MASK) == ADB_PIN_MASK;
}

inline void AdbInterfacePlatform::adb_pin_out()
{
	// (ADB_DDR |= (1 << ADB_DATA_BIT));
	// TODO: ADB_PIN bit id
	gpio_mode_setup(ADB_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, ADB_PIN_MASK);
	// GPIO_MODER(ADB_PORT) = (GPIO_MODER(ADB_PORT) & ~GPIO_MODE_MASK(ADB_PIN_ID))  | GPIO_MODE(ADB_PIN_ID, GPIO_MODE_OUTPUT); 
	
	// SET GPIO_OTYPE_OD
	// GPIO_OTYPER(ADB_PORT) |= ADB_PIN_MASK;
	// GPIO_OSPEEDR(ADB_PORT) = (GPIO_OSPEEDR(ADB_PORT) & ~GPIO_OSPEED_MASK(ADB_PIN_ID)) | GPIO_OSPEED(ADB_PIN_ID, GPIO_OSPEED_2MHZ);
	gpio_set_output_options(ADB_PORT, GPIO_OTYPE_OD, GPIO_OSPEED_2MHZ, ADB_PIN_MASK);
	
}

inline uint16_t AdbInterfacePlatform::wait_data_lo(uint32_t us)
{
	timer_set_period(TIM6, us);
	timer_generate_event(TIM6, TIM_EGR_UG);
	timer_enable_counter(TIM6);
    do {
        if ( !data_in() )
		{
			timer_disable_counter(TIM6);
			return timer_get_counter(TIM6);
			// return clock_micros() - end_time;
		}
            // break;
    }
    while ( TIM_CR1(TIM6) & TIM_CR1_CEN );
    return 0;

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

	timer_set_period(TIM6, us);
	timer_generate_event(TIM6, TIM_EGR_UG);
	timer_enable_counter(TIM6);
	// uint64_t end_time = clock_micros() + us;
    do {
        if ( data_in() )
		{
			timer_disable_counter(TIM6);
			return timer_get_counter(TIM6);
			// return clock_micros() - end_time;
		}
            // break;
    }
    while ( TIM_CR1(TIM6) & TIM_CR1_CEN );

    return 0;
    // do {
    //     if ( data_in() )
    //         break;
    //     adb_delay_us(1 - (6 * 1000000.0 / F_CPU));
    // }
    // while ( --us );
    // return us;

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