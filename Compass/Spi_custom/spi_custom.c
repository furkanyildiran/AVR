#include "spi_custom.h"

#define SPI_BUFF_SIZE 20



void spi_set_dord(uint8_t dord){
	SPCR |= (dord << DORD);
}
void spi_set_cpol_cpha(uint8_t cpol, uint8_t cpha){
	SPCR |= (cpol << CPOL) | (cpha << CPHA);
}

void spi_transmit(uint8_t data){
	PORTB &= ~(1 << SS_pin);
	SPCR &= ~(1 << SPIE);
	uint32_t prev_time = _millis_getMs();
	SPDR = data;
	while ((_millis_getMs() - prev_time) <= 25)
	{
		if(SPSR & (1 << SPIF)){
			PORTB |= (1 << SS_pin);
			break;
		}
	}
}
void spi_master_init(uint8_t clk_dvdr){
	switch(clk_dvdr){
		case SPI_SCK_DVDR2_2X:
		SPSR |= (1 << SPI2X);
		case SPI_SCK_DVDR4:
		SPCR &= ~((1 << SPR1) | (1 << SPR0));
		break;
		
		case SPI_SCK_DVDR8_2X:
		SPSR |= (1 << SPI2X);
		case SPI_SCK_DVDR16:
		SPCR &= ~(1 << SPR1);
		SPCR |= (1 << SPR0);
		break;
		
		case SPI_SCK_DVDR32_2X:
		SPSR |= (1 << SPI2X);
		case SPI_SCK_DVDR64:
		SPCR |= (1 << SPR1);
		SPCR &= ~(1 << SPR0);
		break;
		
		case SPI_SCK_DVDR64_2X:
		SPSR |= (1 << SPI2X);
		case SPI_SCK_DVDR128:
		SPCR |= (1 << SPR1) | (1 << SPR0);
		break;
	}
	DDRB |= (1 << MOSI_pin) | (1 << SS_pin) | (1 << SCK_pin);
	SPCR |= (1 << MSTR) | (1 << SPE);
	PORTB |= (1 << SS_pin);
}