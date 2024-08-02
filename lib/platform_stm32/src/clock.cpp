#include "clock.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/timer.h>

// static volatile uint64_t time_micros;

// extern "C" void sys_tick_handler(void)
// {
// 	time_micros++;
// }

void clock_delay_us(uint16_t x)
{
	timer_set_period(TIM6, x);
	// TIM_ARR(TIM6) = x;
	
	
	timer_generate_event(TIM6, TIM_EGR_UG);
	// TIM_EGR(TIM6) = TIM_EGR_UG;
	
	timer_enable_counter(TIM6);
	// TIM_CR1(TIM6) |= TIM_CR1_CEN;
	// while it is a counter
	while (TIM_CR1(TIM6) & TIM_CR1_CEN);

	// uint64_t end_time = time_micros + x;
	// while (time_micros < end_time);
}
void clock_delay_ms(uint16_t x)
{
	timer_set_period(TIM5, x);
	// TIM_ARR(TIM5) = x;
	
	
	timer_generate_event(TIM5, TIM_EGR_UG);
	// TIM_EGR(TIM5) = TIM_EGR_UG;
	
	timer_enable_counter(TIM5);
	// TIM_CR1(TIM6) |= TIM_CR1_CEN;
	// while it is a counter
	while (TIM_CR1(TIM5) & TIM_CR1_CEN);

	// uint64_t end_time = time_micros + x;
	// while (time_micros < end_time);
}



void clock_init()
{
	// make sure the clock info is right otherwise st link wont work properly. 
	// 		fix: 1. hold BOOTO and press reset.
	//			 2. flash firmware while holding BOOTO 
	// this case its 25 written on the crystal =  25mhz
	// rcc_clock_setup_pll(&rcc_hse_25mhz_3v3[RCC_CLOCK_3V3_168MHZ]);
	rcc_clock_setup_pll(&rcc_hse_25mhz_3v3[RCC_CLOCK_3V3_84MHZ]);
	// rcc_clock_setup_pll(&rcc_hsi_configs[3]);

	
	// make TIM6 a clock that does microseconds
	rcc_periph_clock_enable(RCC_TIM6);
	timer_set_prescaler(TIM6, rcc_apb1_frequency / (1000 * 1000) - 1);
	timer_one_shot_mode(TIM6);
	timer_disable_counter(TIM6);
	timer_set_period(TIM6, 0xffff);

	// make TIM5 a millsecond clock
	rcc_periph_clock_enable(RCC_TIM5);
	timer_set_prescaler(TIM5, rcc_apb1_frequency / (1000) - 1);
	timer_one_shot_mode(TIM5);
	timer_disable_counter(TIM5);
	timer_set_period(TIM5, 0xffff);
	// 168MHz / 168 = 1 MHz = 1 µs 
	// systick_set_reload(168);
	// systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
	// systick_counter_enable();
	// systick_interrupt_enable();
}