#ifdef __cplusplus
extern "C"{
#endif
#ifndef TWI_H_
#define TWI_H_
#define F_CPU 16000000UL
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "_millis.h"

#define TWI_STOP 1
#define TWI_RSTART 0
#define TWI_MW 0
#define TWI_MR 1
#define TWI_SW 2
#define TWI_SR 3
#define TWI_WRITE 0
#define TWI_READ 1
#define twi_ovf_ms 25

struct twi{
	void(*master_init)(uint32_t SCLK);
	void(*send_start)(void);
	void(*send_address)(uint8_t device_addr,uint8_t operation);
	void(*send_byte_with_ack)(uint8_t data);
	void(*send_byte_with_nack)(uint8_t data);
	uint8_t(*read_byte_ret_ack)(void);
	uint8_t(*read_byte_ret_nack)(void);
	void(*send_stop)(void);
	void(*master_reset)(void);
	void(*master_release_bus)(void);
	void(*slave_init)(uint8_t device_addr);
	uint8_t(*slave_listen)(void);
	uint8_t(*control_ovf)(void);
}twi_strct,*twi_ptr;

struct twi* create_twi(void);




#endif 
#ifdef __cplusplus
}
#endif