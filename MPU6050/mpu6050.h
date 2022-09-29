#ifdef __cplusplus
extern "C" {
	#endif

	#ifndef MPU_H_
	#define MPU_H_
	#include "mpu6050_mnemonics.h"
	#include "twi.h"
	#include "kalman_filter.h"

	void mpu_init(uint8_t gyro_fsl, uint8_t accel_fsl);
	void mpu_read_axis(void);
	int16_t mpu_getx(void);
	int16_t mpu_gety(void);
	int16_t mpu_getz(void);

	#endif /* MPU_H_ */

	#ifdef __cplusplus
}
#endif