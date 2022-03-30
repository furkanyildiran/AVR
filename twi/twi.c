#include "twi.h"

void master_init(uint32_t SCLK);
void send_start(void);
void send_address(uint8_t device_addr, uint8_t operation);
void send_byte_with_ack(uint8_t data);
void send_byte_with_nack(uint8_t data);
uint8_t read_byte_ret_ack(void);
uint8_t read_byte_ret_nack(void);
void send_stop(void);
void master_reset(void);
void wait_flag(uint8_t flag);
void master_release_bus(void);
void slave_init(uint8_t device_addr);
uint8_t slave_listen(void);
uint8_t control_ovf(void);
void write_reg_byte(uint8_t device_addr, uint8_t reg_addr, uint8_t reg_val);

uint8_t twi_mode = 0;
uint8_t slave_addressed = 0;
uint8_t twi_ovf_flag = 1;

struct twi* create_twi(void){
	twi_ptr = &twi_strct;
	twi_ptr->master_init = &master_init;
	twi_ptr->send_start = &send_start;
	twi_ptr->send_address = &send_address;
	twi_ptr->send_byte_with_ack = &send_byte_with_ack;
	twi_ptr->send_byte_with_nack = &send_byte_with_nack;
	twi_ptr->read_byte_ret_ack = &read_byte_ret_ack;
	twi_ptr->read_byte_ret_nack = &read_byte_ret_nack;
	twi_ptr->send_stop = &send_stop;
	twi_ptr->master_reset = &master_reset;
	//twi_ptr->set_ovf_ms = &set_ovf_ms;
	//twi_ptr->wait_flag = &wait_flag;
	twi_ptr->master_release_bus = &master_release_bus;
	twi_ptr->slave_init = &slave_init;
	twi_ptr->slave_listen = &slave_listen;
	twi_ptr->control_ovf = &control_ovf;
	return twi_ptr;
}

void master_init(uint32_t SCLK){
	_millis_init();
	TWSR = 0x00;
	//Because pow func is too large for rom memory, not prefer using in this line
	//TWBR = ((F_CPU / SCLK) - 16) / (2 * pow(4, (TWSR & ((1 << TWPS0) | (1 << TWPS1)))));
	//prescaler bits always assumed as 0 therefore prescaler is 1
	TWBR = ((F_CPU / (2 * SCLK)) - 8);
	TWCR = (1 << TWINT) | (1 << TWEN);
	PORTC |= (1 << PORTC4) | (1 << PORTC5);
}
void send_start(void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);
	wait_flag(TWINT);
}
void send_address(uint8_t device_addr, uint8_t operation) {
	TWDR = (device_addr << 1) | operation;
	TWCR = (1 << TWINT) | (1 << TWEN);
	wait_flag(TWINT);
}
void send_byte_with_ack(uint8_t data) {
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	wait_flag(TWINT);
}
void send_byte_with_nack(uint8_t data) {
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	wait_flag(TWINT);
}
uint8_t read_byte_ret_ack(void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	wait_flag(TWINT);
	return TWDR;
}
uint8_t read_byte_ret_nack(void) {
	TWCR = (1 << TWINT) | (1 << TWEN);
	wait_flag(TWINT);
	return TWDR;
}
void send_stop(void) {
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
	wait_flag(TWSTO);
}
void master_reset(void) {
	twi_ovf_flag = 0;
	TWCR = 0;
	PORTC &= ~((1 << PORTC4) | (1 << PORTC5));
	_delay_ms(50);
	PORTC |= (1 << PORTC4) | (1 << PORTC5);
	TWCR = (1 << TWINT) | (1 << TWEN);
}

void wait_flag(uint8_t flag)
{
	uint32_t previous_time = _millis_getMs();
	while (!(TWCR & (1 << flag))) {
		cli();													//cli() and sei() lines have been written for atomic block
		if ((_millis_getMs() - previous_time) > twi_ovf_ms) {   //because comparing values are 32 bit and cpu is 8 bit architecture 
			sei();												//we have to use atomic block by disable interrupts during comparing values
			twi_ovf_flag = 1;
			break;
		}
		sei();
	}
}
void master_release_bus(void) {
	TWCR = 0;
	PORTC &= ~((1 << PORTC4) | (1 << PORTC5));
}
void slave_init(uint8_t slave_addr){
	_millis_init();
	TWAR = (slave_addr << 1);
}
uint8_t slave_listen(void)
{
	if (!slave_addressed) {
		TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT);
		slave_addressed = 1;
		return -1;
		} else {
		if (!(TWCR & (1 << TWINT)))
			return -1;
		else {
			if ((TWSR & 0xF8) == 0xA8)
				twi_mode = TWI_SR;
			else if ((TWSR & 0xF8) == 0x60)
				twi_mode = TWI_SW;
			slave_addressed = 0;
			return twi_mode;
		}
	}
}
uint8_t control_ovf(){
	return twi_ovf_flag;
}