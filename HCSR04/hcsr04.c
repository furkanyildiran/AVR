#include "hcsr04.h"
#define MAX_LOOP_NUM 15535
#define CLOCK_NUM_OF_HIGH_PULSE_LOOP 18
#define SPEED_OF_SOUND_IN_CMS (17165) //at 20 degrees celsius(sound takes the same path 2 times)
#define clok_ns 62.5e-9
#define HCSR04_DDR  DDRB
#define HCSR04_PORT PORTB
#define HCSR04_PIN  PINB
#define TRIG_PIN 1
#define ECHO_PIN 0
#define C1() (high_pulse_width_in_clock=high_pulse_loop_counter*CLOCK_NUM_OF_HIGH_PULSE_LOOP)
#define C2() (d = high_pulse_width_in_clock*PER_CLOCKS_IN_SECONDS*SPEED_OF_SOUND_IN_CMS)


static uint16_t high_pulse_loop_counter = 0;
uint16_t d;
__attribute__((noinline))static void high_pulse_width(){
	high_pulse_loop_counter = 0;
	uint32_t prev_time = _millis_getMs();
	HCSR04_PORT |= (1 << TRIG_PIN);
	_delay_us(10);
	HCSR04_PORT &= ~(1 << TRIG_PIN);
	while(!(HCSR04_PIN&(1 << ECHO_PIN))){
		uint32_t current_time = _millis_getMs();
		if(current_time-prev_time >= 20) break;
	}
	asm volatile("NOP");
	while(HCSR04_PIN&(1 << ECHO_PIN)){
		high_pulse_loop_counter++;
		if(high_pulse_loop_counter == MAX_LOOP_NUM) break;
	}
}
__attribute__((always_inline)) void HCSR04_init(void){
	HCSR04_DDR |= (1 << TRIG_PIN);
	HCSR04_DDR &=~(1 << ECHO_PIN);
}
__attribute__((noinline)) uint16_t HCSR04_distance(void){
	high_pulse_width();
	uint16_t time_width = high_pulse_loop_counter*CLOCK_NUM_OF_HIGH_PULSE_LOOP*(62.5/1000000000)*SPEED_OF_SOUND_IN_CMS;
	
	return time_width;
}