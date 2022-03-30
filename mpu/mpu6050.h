#ifdef __cplusplus
extern "C" {
#endif

#ifndef MPU_H_
#define MPU_H_
#include "mpu6050_mnemonics.h"
#include "twi.h"



void mpu_attach_twi(struct twi *tw_ptr);
void mpu_init(uint8_t gyro_fsl, uint8_t accel_fsl);
void mpu_read_axis(int16_t *x, int16_t *y, int16_t *z);



#endif /* MPU_H_ */

#ifdef __cplusplus
}
#endif