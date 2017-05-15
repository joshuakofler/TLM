/*
 * controlBox_Measurements.c
 *
 * Created: 17.02.2017 12:23:42
 * Author : paddy
 */
#include "measurementsHAL.h" 
#include "controlBoxV01HAL.h"

#include <avr/io.h>
#include <stdint.h>

extern  uint16_t voltageDiv[4];
extern uint16_t voltages[6];
extern uint16_t sensorValue;
extern uint16_t temperature;
 
/*********************************************************************
ADC-Messung des übergebenen Kanals (chan)
10Bit, Polling, 1.1V Referenz, Mittelung von 4 Werten
*********************************************************************/

void measurementHAL_init(void)
{
	TWI1_init();
	//DS1621_init();
}

uint16_t readADC(uint8_t channel)
{
	//  0x00 - ADC0
	//  0x01 - ADC1
	//  0x02 - ADC2
	//  0x03 - ADC3
	//  0x04 - ADC4
	//  0x05 - ADC5
	//  0x06 - ADC6
	//  0x07 - ADC7
	//  0x08 - Temp Sensor

	uint16_t val=0;
	ADMUX = 0xC0 | (channel & 0x0F);			//URef=1.1V, untersten 4 Bits = channel
	ADCSRA = 0x86;							//10Bit, einmalige Messung, kein Interrupt, Systemclock/64
	for (int i=0;i<4;i++)
	{
		ADCSRA|=(1<<ADSC);				//Start der Messung
		while(!(ADCSRA & (1<<ADIF)));		//Warten aufs Ende der Messung
		val+=ADC;
	}
	val = val/4;	        
	return val;
}

uint16_t getChipTemperature(void)
{
	uint16_t temp = 0;
	// not evalluated
	temp = readADC(0x08);
	return temp;
}

void getAmbientTemperature(void)
{
	temperature = DS1621_getTemperature();
}

void getAllVoltages(void)
{
	voltages[0] = readADC(0x00) *25.741;
	voltages[1] = readADC(0x01) *25.741;
	voltages[2] = readADC(0x02) *25.741;
	voltages[3] = readADC(0x03) *25.741;
	voltages[4] = readADC(0x04) *25.741;
	voltages[5] = readADC(0x05) *25.741;
}

void getAllDivVoltages(void)
{
	voltageDiv[0] = (readADC(0x04) - readADC(0x00)) *25.741;
	voltageDiv[1] = (readADC(0x05) - readADC(0x01)) *25.741;
	voltageDiv[2] = (readADC(0x04) - readADC(0x02)) *25.741;
	voltageDiv[3] = (readADC(0x05) - readADC(0x03)) *25.741;
}

void getSensorValue(uint8_t sensortype)
{
	uint16_t val = 0;
	val = readADC(0x06) * (1100/1024);
	if (sensortype)
	{
		sensorValue = val * (1000/47); // Messung µA ueber einen 47R Widerstand
	}
	else
	{
		sensorValue = sensorValue*11; //Messung mv
	}

}