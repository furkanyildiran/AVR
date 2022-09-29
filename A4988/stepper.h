#ifndef STEPPER_H_
#define STEPPER_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "stepper_config.h"

#define A4988_555_Hz 225	//1.8ms period
#define A4988_588_Hz 211	//1.7ms period
#define A4988_625_Hz 199	//1.6ms period
#define A4988_666_Hz 187	//1.5ms period
#define A4988_714_Hz 174	//1.4ms period
#define A4988_SPEED_LEVEL1() do{OCR0A = A4988_555_Hz;}while(0)
#define A4988_SPEED_LEVEL2() do{OCR0A = A4988_588_Hz;}while(0)
#define A4988_SPEED_LEVEL3() do{OCR0A = A4988_625_Hz;}while(0)
#define A4988_SPEED_LEVEL4() do{OCR0A = A4988_666_Hz;}while(0)
#define A4988_SPEED_LEVEL5() do{OCR0A = A4988_714_Hz;}while(0)

#define R_DDR_VAL			((1<<R_dir_pin)|(1<<R_sleep_pin)|(1<<R_step_pin))
#define L_DDR_VAL			((1<<L_dir_pin)|(1<<L_sleep_pin)|(1<<L_step_pin))
#define R_SET_PINS_OUTPUT()	do{R_A4988_DDR |= R_DDR_VAL;}while(0)
#define L_SET_PINS_OUTPUT()	do{L_A4988_DDR |= L_DDR_VAL;}while(0)
#define TIMER0_CTC_MODE		(1<<WGM01)
#define TIMER0_PRESCALER_64 ((1 << CS01) | (1 << CS00))
#define TIMER0_INT_ENBL		(1<<OCIE0A)

#define STOP		0
#define FORWARD		1
#define LEFT		2
#define RIGHT		3
#define BACKWARD	4

#define R_ON()	do{R_A4988_PORT |= (1 << R_sleep_pin);}while(0)
#define R_OFF() do{R_A4988_PORT &=~(1 << R_sleep_pin);}while(0)
#define L_ON()	do{L_A4988_PORT |= (1 << L_sleep_pin);}while(0)
#define L_OFF() do{L_A4988_PORT &=~(1 << L_sleep_pin);}while(0)
	
#define STEP_PULSE()	do{R_A4988_PORT ^= (1 << R_step_pin); L_A4988_PORT ^= (1 << L_step_pin);}while(0)
#define CHIP_SLEEP()	do{R_OFF(); L_OFF();}while(0)
#define CHIP_ACTIVE()	do{R_ON(); L_ON();}while(0)

#define FORWARD_DIRECTION()		do{CHIP_ACTIVE(); R_A4988_PORT &=~(1<<R_dir_pin); L_A4988_PORT &=~(1<<L_dir_pin);}while(0)
#define BACKWARD_DIRECTION()	do{CHIP_ACTIVE(); R_A4988_PORT |= (1<<R_dir_pin); L_A4988_PORT |= (1<<L_dir_pin);}while(0)
#define RIGHT_DIRECTION()		do{CHIP_ACTIVE(); R_A4988_PORT |= (1<<R_dir_pin); L_A4988_PORT &=~(1<<L_dir_pin);}while(0)
#define LEFT_DIRECTION()		do{CHIP_ACTIVE(); R_A4988_PORT &=~(1<<R_dir_pin); L_A4988_PORT |= (1<<L_dir_pin);}while(0)
#define	STOP_DIRECTION()		do{CHIP_SLEEP();}while(0)
	
void A4988_init(void);
void A4988_forward(void);
void A4988_backward(void);
void A4988_left(void);
void A4988_right(void);
void A4988_stop();
	
#endif /* STEPPER_H_ */