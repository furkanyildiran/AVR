#ifdef __cplusplus
extern "C"{
	#endif
	#ifndef COMPASS_H_
	#define COMPASS_H_
	#include <math.h>
	#include "mpu6050.h"
	#include "qmc5883l.h"
	
	uint16_t compass_get_degree(void){
		qmc_read_axis();
		mpu_read_axis();
		
		int16_t mx = mpu_getx();
		int16_t my = mpu_gety();
		int16_t mz = mpu_getz();
		int16_t qx = qmc_getx();
		int16_t qy = qmc_gety();
		int16_t qz = qmc_getz();
		
		double pitch = atan2((double) -mx, sqrt((long)mz*(long)mz + (long)my*(long)my));
		double roll = atan2((double)my, sqrt((long)mz*(long)mz  + (long)mx*(long)mx));

		double X_h = (double)qx * cos(pitch) + (double)qy * sin(roll) * sin(pitch) + (double)qz * cos(roll) * sin(pitch);
		double Y_h = (double)qy * cos(roll) - (double)qz * sin(roll);
		double azimuth = atan2(Y_h, X_h);
		if (azimuth < 0) {
			azimuth = 2 * M_PI + azimuth;
		}
		azimuth = (azimuth * 180.0 / 3.14);
		return (uint16_t)azimuth;
	}

	#endif
	#ifdef __cplusplus
}
#endif