#include "mpu6050.h"

static int16_t x,y,z;
static struct KALMAN kx = {0,1,0}, ky = {0,1,0}, kz = {0,1,0};

static void write_reg_byte(uint8_t reg_addr, uint8_t reg_val){
	twi_send_start();
	twi_send_address(MPU_ADDR, TWI_WRITE);
	twi_send_byte_with_nack(reg_addr);
	twi_send_byte_with_nack(reg_val);
	twi_send_stop();
}

uint8_t read_byte(uint8_t reg_addr){
	twi_send_start();
	twi_send_address(MPU_ADDR, TWI_WRITE);
	twi_send_byte_with_nack(reg_addr);
	twi_send_start();
	twi_send_address(MPU_ADDR, TWI_READ);
	uint8_t byte = twi_read_byte_ret_nack();
	twi_send_stop();
	return byte;
}

void mpu_init(uint8_t gyro_fsl, uint8_t accel_fsl){
	write_reg_byte(MPU_PWR_MGMT_1_REG, 0x00);
	write_reg_byte(MPU_CONFIG_REG, MPU_CONFIG_DLPF_CFG_1kHz);
	write_reg_byte(MPU_GYRO_CONFIG_REG, gyro_fsl);
	write_reg_byte(MPU_ACCEL_CONFIG_REG, accel_fsl);	
}

void mpu_read_axis(void){
	uint8_t bytes[6] = {0};
	for(uint8_t i = 0; i < 6; i++){
		bytes[i] = read_byte(MPU_ACCEL_XOUT_H_REG + i);
	}
 	x = ((bytes[0] << 8) | bytes[1]) + MPU_xoffset;
	y = ((bytes[2] << 8) | bytes[3]) + MPU_yoffset;
	z = ((bytes[4] << 8) | bytes[5]) + MPU_zoffset;
	if(twi_control_ovf()){
		twi_master_reset();
		x = 0;
		y = 0;
		z = 0;
	}
	x = kalman_calculate(&kx, x, MPU_NOISE_VARIANCE, 10);
	y = kalman_calculate(&ky, y, MPU_NOISE_VARIANCE, 10);
	z = kalman_calculate(&kz, z, MPU_NOISE_VARIANCE, 10);
}
int16_t mpu_getx(){
	return x;
}
int16_t mpu_gety(){
	return y;
}
int16_t mpu_getz(){
	return z;
}