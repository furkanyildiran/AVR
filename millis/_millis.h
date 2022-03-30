#ifdef __cplusplus
extern "C"{
	#endif

	#ifndef __MILLIS_H__
	#define __MILLIS_H__
	#define F_CPU 16000000UL
	#include <stdint.h>
	#include <avr/io.h>
	#include <avr/interrupt.h>

	void _millis_init(void);
	uint32_t _millis_getMs(void);

	#endif
	#ifdef __cplusplus
}
#endif
