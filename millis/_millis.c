#include "_millis.h"

static volatile uint32_t _milliseconds = 0;

ISR(TIMER0_COMPA_vect) {
	_milliseconds++;
}

void _millis_init(void)
{
	TCCR0A = (1 << WGM01);
	TCCR0B = (1 << CS01) | (1 << CS00);
	TCNT0 = 0;
	OCR0A = 249;
	TIMSK0 = (1 << OCIE0A);
}

uint32_t _millis_getMs(void) {
	return _milliseconds;
}