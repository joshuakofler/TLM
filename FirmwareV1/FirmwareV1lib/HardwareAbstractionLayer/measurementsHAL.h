/*
 * measurementsHAL.h
 *
 * Created: 20-Apr-17 3:07:49 PM
 *  Author: Jenny Patrick
 *  Editor: Kofler Joshua
 */ 
 
#ifndef MEASUREMENTSHAL_H_
#define MEASUREMENTSHAL_H_

#include <stdint.h>
#include <avr/io.h>

void measurementHAL_init(void);

uint16_t readADC(uint8_t channel);

void getAllVoltages(void);

void getAllDivVoltages(void);

uint16_t getChipTemperature(void);

void getAmbientTemperature(void);

void getSensorValue(uint8_t type);

#endif /* MEASUREMENTS_HAL_H_ */