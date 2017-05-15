/*
 * measurements.c
 *
 * Created: 17.02.2017 20:35:06
 *  Author: paddy
 */ 
#include "HardwareAbstractionLayer/controlBoxV01HAL.h"
#include "HardwareAbstractionLayer/measurementsHAL.h"
#include "measurements.h"

static enum states{ADVANCED, SIMPLE, WAIT} state;

extern uint16_t bounds[7];
extern uint16_t voltages[6];
extern uint16_t voltageDiv[4];
extern uint8_t statusCode;
extern uint8_t measurementLED_valid;

uint8_t nLED;
uint8_t measCount = 0;
timer_var_t measTimer;

void measurement_init(void)
{
	/* initialize bounds */
	bounds[0] = 1880;
	bounds[1] = 4760;
	bounds[2] = 7640;
	bounds[3] = 10520;
	bounds[4] = 13000;
	bounds[5] = 15200;
	bounds[6] = 22000;

	state = WAIT;
	measTimer = TIMER_SEC(1);
	
	measurementHAL_init();
}

void measurement_process(void)
{
	if (!measurementLED_valid)
	{
		measTimer = TIMER_SEC(1);
		state = WAIT;
	}
	
	switch(state)
	{
		case ADVANCED:
			measCount = 0;

			//getAmbientTemperature();
			getSensorValue(0);			
			getAllVoltages();
			getAllDivVoltages();
			
			nLED = 0;
			for (uint8_t i = 0; i < 4; i++)
			{
				if (voltageDiv[i] < bounds[6])
				{
					for (uint8_t ii = 0; ii < 6; ii++)
					{
						if (voltageDiv[i] > bounds[ii])
						{
							nLED++;
						}
					}
				}
			}
			
			if (nLED > 12) {
				statusCode = 0x07;
			}
			else {
				statusCode = 0x00;
			}
			statusCode |= (nLED << 3);

			state = WAIT;
			measTimer = TIMER_SEC(3);
		break;
		
		case SIMPLE:		//STATE MEAS_SIMP
			measCount++;

			//getAmbientTemperature();
			getAllDivVoltages();
			
			nLED=0;
			for (uint8_t i = 0; i<4; i++)
			{
				if (voltageDiv[i] < bounds[6])
				{
					for (uint8_t ii = 0; ii<6; ii++)
					{
						if (voltageDiv[i] >= bounds[ii])
						{
							nLED++;							
						}
					}
				}
			}
			
			if (nLED > 12) {
				statusCode = 0x07;
			}
			else {
				statusCode = 0x00;	
			}
			statusCode |= (nLED << 3);

			state = WAIT;
			measTimer = TIMER_SEC(1);
		break;
		
		case WAIT:
			if (measTimer == 0)
			{
				if (measCount >= 10)
				{
					state = ADVANCED;
				}
				else
				{
					state = SIMPLE;
				}
			}
		break;
	}
}