/*
 * FirmwareV1.c
 *
 * Created: 06-Apr-17
 *  Author: Kofler Joshua
 *  Editor: Jenny Patrick
 */ 
//////////////////////////////////////////////////////////////////////////
// important intern saved variables / includes

#define F_CPU	16000000UL
 
#include <avr/io.h>
#include <stdint.h>

#include "C:\Users\Admin\Google Drive\projects\TLM\FirmwareV1\FirmwareV1lib\HardwareAbstractionLayer\controlBoxV01HAL.h"
#include "C:\Users\Admin\Google Drive\projects\TLM\FirmwareV1\FirmwareV1lib\protocolabstraction.c"
#include "C:\Users\Admin\Google Drive\projects\TLM\FirmwareV1\FirmwareV1lib\measurements.h"
#include "C:\Users\Admin\Google Drive\projects\TLM\FirmwareV1\FirmwareV1lib\lightcontrol.h"

TIMERS(&measTimer, &lightTimer);

//////////////////////////////////////////////////////////////////////////
// global variables

/* initialize intern stored address */
uint16_t address = 0x0000;
/* intern stored toolID = 001 (handrail) */
uint8_t toolID = 0x01;

/* 4-Bit LED/sensor status code */
uint8_t statusCode;

/* 7 bounds */
uint16_t bounds[7];

/* 4 voltages */
uint16_t voltages[6];

/* 4 div voltages */
uint16_t voltageDiv[4];

/* 10-Bit ADC06 value (sensor) */
uint16_t sensorValue;

/* 10-Bit ADC08 value (temperature) */
int16_t temperature;

/* LED brightness */
uint8_t brightness;

/* LED MODE					*/
/*	OFF					0x00
 *	ON					0x01
 *	custom brightness	0x02
 *	blink				0x03
 */ uint8_t lightmode;

/* bool (if measurement is possible) */
uint8_t measurementLED_valid = 0;

/* error code */
uint8_t errorCode = 0x00;


//////////////////////////////////////////////////////////////////////////
// state machine

/* important definitions for the state machine */
uint8_t state;

void stateMachine(void)
{
	switch (state)
	{
		case 0:			/* normal operation state */
			lightcontrol_process();
			measurement_process();
			state = 1;
		break;
		
		case 1:			/* bus evaluation state */
			bus_process();
		 	state = 0;
		break;

		default:
			state = 0;		/* reset the state machine */
		break;
	}
}


int main(void)
{
	sei();
	/* initialize hardware abstraction layer */
	HAL_init();
	/* initialize main features */
	lightcontrol_init();
	measurement_init();

	/* some testing */
	lightmode = 0x01;
	brightness = 50;
	state = 0;

    while (1) 
    {
		HAL_process();
		stateMachine();
    }
}

