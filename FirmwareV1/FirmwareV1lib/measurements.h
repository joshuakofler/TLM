/*
 * measurements.h
 *
 * Created: 20-Apr-17 3:18:58 PM
 *  Author: Jenny Patrick
 *  Editor: Kofler Joshua
 */ 


#ifndef MEASUREMENTS_H_
#define MEASUREMENTS_H_

#include "HardwareAbstractionLayer/controlBoxV01HAL.h"
#include "HardwareAbstractionLayer/measurementsHAL.h"

extern timer_var_t measTimer;

void measurement_init(void);
void measurement_process(void);

#endif /* MEASUREMENTS_H_ */