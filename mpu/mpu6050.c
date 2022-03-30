#include "mpu6050.h"



struct twi *mpu_twi;

static void write_reg_byte(uint8_t reg_addr, uint8_t reg_val){
	mpu_twi->send_start();
	mpu_twi->send_address(MPU_ADDR, TWI_WRITE);
	mpu_twi->send_byte_with_nack(reg_addr);
	mpu_twi->send_byte_with_nack(reg_val);
	mpu_twi->send_stop();
}

uint8_t read_byte(uint8_t reg_addr){
	mpu_twi->send_start();
	mpu_twi->send_address(MPU_ADDR, TWI_WRITE);
	mpu_twi->send_byte_with_nack(reg_addr);
	mpu_twi->send_start();
	mpu_twi->send_address(MPU_ADDR, TWI_READ);
	uint8_t byte = mpu_twi->read_byte_ret_nack();
	mpu_twi->send_stop();
	return byte;
}

void mpu_attach_twi(struct twi *tw_ptr){
	mpu_twi = tw_ptr;
}

void mpu_init(uint8_t gyro_fsl, uint8_t accel_fsl){
	write_reg_byte(MPU_PWR_MGMT_1_REG, 0x00);
	write_reg_byte(MPU_CONFIG_REG, MPU_CONFIG_DLPF_CFG_1kHz);
	write_reg_byte(MPU_GYRO_CONFIG_REG, gyro_fsl);
	write_reg_byte(MPU_ACCEL_CONFIG_REG, accel_fsl);	
}

void mpu_read_axis(int16_t *x, int16_t *y, int16_t *z){
	uint8_t bytes[6] = {0};
	for(uint8_t i = 0; i < 6; i++){
		bytes[i] = read_byte(MPU_ACCEL_XOUT_H_REG + i);
	}
cli();	
 	*x = (bytes[0] << 8) | bytes[1];
	*y = (bytes[2] << 8) | bytes[3];
	*z = (bytes[4] << 8) | bytes[5];
sei();
}
