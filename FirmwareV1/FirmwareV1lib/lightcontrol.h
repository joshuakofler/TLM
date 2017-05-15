/*
 * lightcontrol.h
 *
 * Created: 20-Apr-17 11:41:44 AM
 *  Author: Jenny Patrick
 *  Editor: Kofler Joshua
 */ 


#ifndef LIGHTCONTROL_H_
#define LIGHTCONTROL_H_

#include "HardwareAbstractionLayer/controlBoxV01HAL.h"
#include "HardwareAbstractionLayer/lightcontrolHAL.h"

extern timer_var_t lightTimer;

void lightcontrol_init(void);

void lightcontrol_process(void);

#endif /* LIGHTCONTROL_H_ */