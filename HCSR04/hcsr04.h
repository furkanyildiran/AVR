#ifdef __cplusplus
extern "C"{
#endif
#ifndef HCSR04_H_
#define HCSR04_H_
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "_millis.h"

__attribute__((always_inline)) void HCSR04_init(void);
__attribute__((noinline)) uint16_t HCSR04_distance(void);

#endif /* HCSR04_H_ */
#ifdef __cplusplus
}
#endif