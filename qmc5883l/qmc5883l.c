#include "qmc5883l.h"

#define x_offset 260
#define y_offset -137
#define z_offset -421
#define x_scale 1
#define y_scale 1
#define z_scale 1



void qmc_attach_twi(struct twi *twi_addr){
	qmc_twi = twi_addr;
}

void write_reg_byte(uint8_t reg_addr, uint8_t reg_val){
	qmc_twi->send_start();
	qmc_twi->send_address(QMC_ADDRESS, TWI_WRITE);
	qmc_twi->send_byte_with_nack(reg_addr);
	qmc_twi->send_byte_with_nack(reg_val);
	qmc_twi->send_stop();
}

void qmc_init(uint8_t osr, uint8_t rng, uint8_t odr, uint8_t intrpt){
	uint8_t control1_val = (osr << 6) | (rng << 4) | (odr << 2) | QMC_MODE_CONTINUOUS;
	uint8_t control2_val = (1 << 6 ) | intrpt;
	write_reg_byte(QMC_CONTOL1_REG, control1_val);
	write_reg_byte(QMC_CONTOL2_REG, control2_val);
	write_reg_byte(QMC_SETPRD_REG, 1);              //recommended setting by qmc datasheet
}

void qmc_read_axis(int16_t *x, int16_t *y, int16_t *z){
	int16_t data[7] = {0};
	qmc_twi->send_start();
	qmc_twi->send_address(QMC_ADDRESS, TWI_WRITE);
	qmc_twi->send_byte_with_nack(QMC_X_LSB_REG);
	qmc_twi->send_start();
	qmc_twi->send_address(QMC_ADDRESS, TWI_READ);
	for(uint8_t i = 0; i < 6; i++)
		data[i] = qmc_twi->read_byte_ret_ack();
	data[6] = qmc_twi->read_byte_ret_nack();
	qmc_twi->send_stop();
	cli();
	*x = (data[1] << 8) | data[0];
	*y = (data[3] << 8) | data[2];
	*z = (data[5] << 8) | data[4];
	//*x = (*x - x_offset) * x_scale;
	//*y = (*y - y_offset) * y_scale;
	//*z = (*z - z_offset) * z_scale;
	sei();
}
void qmc_soft_reset(void){
	write_reg_byte(QMC_CONTOL2_REG, (1<<7));
}
