#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "_millis.h"
#include "spi_custom.h"
#include "pcd8544.h"
#include "mpu6050.h"
#include "qmc5883l.h"
#include "compass.h"

int main(void)
{
	_millis_init();
	twi_master_init(200000);
	qmc_init(QMC_OSR_64, QMC_RNG_2G, QMC_ODR_50HZ, QMC_DSBL_INTRPT);
	mpu_init(MPU_GYRO_FSL250,MPU_ACCEL_FS_2G);
	
	spi_master_init(SPI_SCK_DVDR4);
	spi_set_cpol_cpha(SPI_CPOL_LEDNG_EDG_RISNG,SPI_CPHA_LEDNG_EDG_SMPLE);
	spi_set_dord(SPI_DORD_MSB_FIRST);
	
	PCD_pins(PB1,PB0);
	PCD_init();
	uint32_t prev_time = 0;
	char data[10] = {"\0"};
		
	sei();
	while (1)
	{
		int16_t degree = compass_get_degree();
		if((_millis_getMs() - prev_time) > 800){
			
			PCD_clear_all();
			sprintf(data,"%d",degree);
			PCD_text(data,0,LINE_0);
			prev_time = _millis_getMs();
		}
	}
	return 0;
}

