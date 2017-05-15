/*
 * lightcontrol.c
 *
 * Created: 06-Apr-17
 *  Author: Patrick Jenny
 *  Editor: Kofler Joshua
 */ 
//////////////////////////////////////////////////////////////////////////
// important intern saved variables / includes

#include "lightcontrol.h"
#include "HardwareAbstractionLayer/controlBoxV01HAL.h"
#include "HardwareAbstractionLayer/lightcontrolHAL.h"

extern uint8_t brightness;
extern uint8_t lightmode;
extern uint8_t measurementLED_valid;

timer_var_t lightTimer;

 void lightcontrol_init(void)
 {
	/* initialize state */
	lightmode = 0x01;
	/* initialize measurement-validity */
	measurementLED_valid = 1;
	/* initialize lightcontrolHAL */
	lightcontrolHAL_init();
 }

 void lightcontrol_process(void)
 {
	switch (lightmode)
	{
		case 0x00:	/* case fully off */
			setbrightness_FULLOFF();
			brightness = 0;
			measurementLED_valid = 0;
		break;

		case 0x01:	/* case fully on */
			setbrightness_FULLON();
			brightness = 255;
			measurementLED_valid = 1;
		break;

		case 0x02:	/* case costume brightness */
			setbrightness(brightness);
			measurementLED_valid = 0;
		break;

		case 0x03:	/* case blink mode (0.5 Hz) */
			/* invert output-pin after timer is 0 */
			if (lightTimer == 0)
			{
				invbrightness();
				/* fixed blink frequency (0.5 Hz) */
				lightTimer = TIMER_SEC(1);
			}
			measurementLED_valid = 0;
		break;

		default:
			/* reset to default */
			lightmode = 0x01;
		break;
	}
 }