/*
 * lightcontrolHAL.h
 *
 * Created: 20-Apr-17 11:49:49 AM
 *  Author: Jenny Patrick
 *  Editor: Kofler Joshua
 */ 


#ifndef LIGHTCONTROLHAL_H_
#define LIGHTCONTROLHAL_H_

#include <stdint.h>
#include <avr/io.h>

void lightcontrolHAL_init(void);

void setbrightness_FULLOFF(void);

void setbrightness_FULLON(void);

void setbrightness(uint8_t _brightness);

void invbrightness(void);

#endif /* LIGHTCONTROLHAL_H_ */