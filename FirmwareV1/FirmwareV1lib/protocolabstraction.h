/*
 * protocolabstraction.h
 *
 * Created: 21-Apr-17 9:30:31 AM
 *  Author: Kofler Joshua
 *  Editor: Jenny Patrick
 */ 


#ifndef PROTOCOLABSTRACTION_H_
#define PROTOCOLABSTRACTION_H_

#include "HardwareAbstractionLayer/controlBoxV01HAL.h"

uint8_t flag = 0;
uint16_t length = 0;

/* state machine */
extern uint8_t state;
/* intern saved toolID */
extern uint8_t toolID;

/* error-code */
extern uint8_t errorCode;

/* command */
uint8_t mode;

/* temp variable */
uint16_t temp;

/* START/STOP Condition */
uint8_t START = 0xA0;
uint8_t STOP = 0x09;

uint8_t frame[37];

uint16_t receiveCount = 3;
uint16_t receiveLength = 0;
uint8_t receiveFlag	= 0;

#define MODEADR				1
extern uint16_t address;

#define MODESTD				2

#define MODEDEV				3
uint8_t deviceSTART = 0x50;
uint8_t deviceSTOP = 0x06;

#define MODESPE				4

#define MODETST				5

#define MODEHEL				6

#define MODECTR				7
uint16_t varValue;
uint8_t varID;
	#define statusCodeID		1
	extern uint8_t statusCode;

	#define bounds1ID			2
	#define bounds2ID			3
	#define bounds3ID			4
	#define bounds4ID			5
	#define bounds5ID			6
	#define bounds6ID			7
	#define bounds7ID			8
	extern uint16_t bounds[];

	#define voltages1ID			9
	#define voltages2ID			10
	#define voltages3ID			11
	#define voltages4ID			12
	#define voltages5ID			13
	#define voltages6ID			14
	extern uint16_t voltages[];

	#define voltageDiv1ID		15
	#define voltageDiv2ID		16
	#define voltageDiv3ID		17
	#define voltageDiv4ID		18
	extern uint16_t voltageDiv[];

	#define sensorValueID		19
	extern uint16_t sensorValue;

	#define temperatureID		20
	extern int16_t temperature;

	#define brightnessID		21
	extern uint8_t brightness;

	#define lightmodeID			22
	extern uint8_t lightmode;

//////////////////////////////////////////////////////////////////////////
// bus system buffer

#define BUFFERSIZE	150

uint8_t buffer[BUFFERSIZE];
uint8_t writePointer;
uint8_t readPointer;

uint8_t bufferU1[BUFFERSIZE];
uint8_t writePointerU1;
uint8_t readPointerU1;

/* protocol abstraction process */
void bus_process(void);

#endif /* PROTOCOLABSTRACTION_H_ */