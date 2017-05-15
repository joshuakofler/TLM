/*
 * lightcontrolHAL.c
 *
 * Created: 06-Apr-17
 *  Author: Patrick Jenny
 *  Editor: Kofler Joshua
 */

 #include "lightcontrolHAL.h"

void lightcontrolHAL_init(void)
{
	/* Set PD6 as output */
	DDRD |= (1 << DDRD6);
	/* initialize Timer */
	/* PWM Mode | Mode 3 - Fast PWM - | frequency = 7843 kHz */
	TCCR0A = 0b11000011;
	TCCR0B = 0b00000010;
}

void setbrightness_FULLOFF(void)
{
	/* disable Timer-Output and set PD6 to high */
	TCCR0A &= ~((1 << COM0A0) | (1 << COM0A1));
	PORTD |= (1 << PORTD6);
}

void setbrightness_FULLON(void)
{
	/* disable Timer-Output and set PD6 to low */
	TCCR0A &= ~((1 << COM0A1) | (1 << COM0A0));
	PORTD &= ~(1 << PORTD6);
}

void setbrightness(uint8_t _brightness)
{
	/* enable Timer-Output and set OCR0A register */
	TCCR0A |= ((1 << COM0A0) | (1 << COM0A1));
	OCR0A = _brightness;
}

void invbrightness(void)
{
	/* disable PWM when active */
	if (TCCR0A & ((1 << COM0A1) | (1 << COM0A0)))
	{
		TCCR0A &= ~((1 << COM0A1) | (1 << COM0A0));
	}
	/* invert PD6 */
	PORTD ^= (1 << PORTD6);
}