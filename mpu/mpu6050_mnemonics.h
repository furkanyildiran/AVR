#ifdef __cplusplus
extern "C" {
#endif

#ifndef MPU_MNEMONICS_H_
#define MPU_MNEMONICS_H_

#define MPU_ADDR		 0x68
#define MPU_SMPLRT_DIV_REG	 0x19
#define MPU_CONFIG_REG		 0x1A
#define MPU_GYRO_CONFIG_REG	 0x1B
#define MPU_ACCEL_CONFIG_REG	 0x1C
#define MPU_FIFO_EN_REG		 0x23
#define MPU_INT_PIN_CFG_REG	 0x37
#define MPU_INT_ENABLE_REG	 0x38
#define MPU_INT_STATUS_REG	 0x3A
#define MPU_ACCEL_XOUT_H_REG	 0x3B
#define MPU_ACCEL_XOUT_L_REG	 0x3C
#define MPU_ACCEL_YOUT_H_REG	 0x3D
#define MPU_ACCEL_YOUT_L_REG	 0x3E
#define MPU_ACCEL_ZOUT_H_REG	 0x3F
#define MPU_ACCEL_ZOUT_L_REG	 0x40
#define MPU_TEMP_OUT_H_REG	 0x41
#define MPU_TEMP_OUT_L_REG	 0x42
#define MPU_GYRO_XOUT_H_REG	 0x43
#define MPU_GYRO_XOUT_L_REG	 0x44
#define MPU_GYRO_YOUT_H_REG	 0x45
#define MPU_GYRO_YOUT_L_REG	 0x46
#define MPU_GYRO_ZOUT_H_REG	 0x47
#define MPU_GYRO_ZOUT_L_REG	 0x48
#define MPU_SIGNAL_PATH_RES_REG  0x68
#define MPU_USER_CTRL_REG	 0x6A
#define MPU_PWR_MGMT_1_REG	 0x6B
#define MPU_PWR_MGMT_2_REG	 0x6C
#define MPU_FIFO_COUNTH_REG	 0x72
#define MPU_FIFO_COUNTL_REG      0x73
#define MPU_FIFO_R_W_REG	 0x74
#define MPU_WHO_AM_I_REG	 0x75
#define MPU_ACCEL_FS_2G          0x00
#define MPU_ACCEL_FS_4G		 0x08
#define MPU_ACCEL_FS_8G		 0x10
#define MPU_ACCEL_FS_16G         0x18
#define MPU_TEMP_FIFO_EN	 0x80
#define MPU_XG_FIFO_EN		 0x40
#define MPU_YG_FIFO_EN		 0x20
#define MPU_ZG_FIFO_EN		 0x10
#define MPU_ACCEL_FIFO_EN	 0x08
#define MPU_GYRO_FSL250          0x00
#define MPU_GYRO_FSL500          0x08
#define MPU_GYRO_FSL1000         0x10
#define MPU_GYRO_FSL2000         0x18
#define MPU_FIFO_ENBL_WR         0x40
#define MPU_FIFO_DSBL_WR         0x00
#define MPU_CONFIG_DLPF_CFG_1kHz 0x01
#define MPU_FIFO_DATA_TEMP       0x80
#define MPU_FIFO_DATA_XG         0x40
#define MPU_FIFO_DATA_YG         0x20
#define MPU_FIFO_DATA_ZG         0x10
#define MPU_FIFO_DATA_ACCEL      0x08
#define MPU_FIFO_DATA_NO         0x00
#define MPU_SMPLRT_DIV_8         0x08          
#define MPU_NOISE_VARIANCE       1700 //+-1700

#endif /* MPU_MNEMONİCS_H_ */

#ifdef __cplusplus
}
#endif