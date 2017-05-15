/*
 * controlBoxV01HAL.h
 *
 * Created: 15-Apr-17 11:58:26 AM
 *  Author: Kofler Joshua
 *  Editor: Jenny Patrick
 */ 

 #include <stdint.h>

#ifndef CONTROLBOXV01HAL_H_
#define CONTROLBOXV01HAL_H_

/* initialize hardware abstraction layer */
void HAL_init(void);
/* hardware abstraction layer process */
void HAL_process(void);

/* timer definitions */
typedef uint32_t timer_var_t;
typedef timer_var_t * const timer_array_t[];
extern timer_array_t hal_timers;

#define TIMER_DISABLED (timer_var_t)-1
#define TIMER_MSEC(v) ((v)*1000ul)
#define TIMER_SEC(v) ((v)*1000000ul)
#define TIMER_MINUTE(v) ((v)*60000000ul)
#define TIMERS(...) timer_array_t hal_timers={__VA_ARGS__, 0};

/* initialize the USART0 interface */
void USART0_init(void);
/* set MAX458 into receive mode */
void USART0_setToReceive(void);
/* set MAX458 into transmit mode */
void USART0_setToTransmit(void);
/* send a char over the USART0 interface */
void USART0_sendChar(unsigned char data);
/* send a string over the USART0 interface */
void USART0_sendString(unsigned char *s);
/* send string with specific length over the USART0 interface */
void USART0_sendStringWL(unsigned char *s, unsigned char length);
/* flush the USART0 buffer */
void USART0_flush(void);
/* receive a char over the USART0 interface */
unsigned char USART0_receive(void);
/* check if there is any error on the USART0 interface */
unsigned char USART0_isError(void);

/* initialize the USART1 interface */
void USART1_init(void);
/* set MAX458 into receive mode */
void USART1_setToReceive(void);
/* set MAX458 into transmit mode */
void USART1_setToTransmit(void);
/* send char over the USART1 interface */
void USART1_sendChar(unsigned char data);
/* send string over the USART1 interface */
void USART1_sendString(unsigned char *s);
/* send string with specific length over the USART1 interface */
void USART1_sendStringWL(unsigned char *s, unsigned char length);
/* flush the USART1 buffer */
void USART1_flush(void);
/* receive a char over the USART1 interface */
unsigned char USART1_receive(void);
/* check if there is any error on the USART1 interface */
unsigned char USART1_isError(void);

/* initialize the TWI0 interface */
void TWI0_init(void);
/* terminates the data transfer and releases the TWI0 bus */
void TWI0_stop(void);
/* issues a start condition and sends address and transfer direction */
unsigned char TWI0_start(unsigned char addr);
/* send one byte to the TWI device */
unsigned char TWI0_write(unsigned char data);
/*receive one byte from the TWI device */
unsigned char TWI0_readAck(void);
/*receive one byte from the TWI device */
unsigned char TWI0_readNAck(void);

/* initialize the TWI1 interface */
void TWI1_init(void);
/* terminates the data transfer and releases the TWI1 bus */
void TWI1_stop(void);
/* issues a start condition and send address and transfer direction */
unsigned char TWI1_start(unsigned char addr);
/* send one byte to the TWI device */
unsigned char TWI1_write(unsigned char data);
/* receive one byte from the TWI device */
unsigned char TWI1_readAck(void);
/* receive one byte from the TWI device */
unsigned char TWI1_readNAck(void);

/* initialize the EAT123 display */
void EAT123_init(void);
/* write char out to display on current position */
void EAT123_write(unsigned char *output, unsigned char line);

/* initialize temperature sensor DS1621 */
void DS1621_init(void);
/* get temperature */
int16_t DS1621_getTemperature(void);

#endif /* CONTROLBOXV01HAL_H_ */