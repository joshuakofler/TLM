/*
 * protocolabstraction.c
 *
 * Created: 06-Apr-17 10:58:31 AM
 *  Author: Kofler Joshua
 *	Editor: Jenny Patrick
 */
#include "protocolabstraction.h"
#include "HardwareAbstractionLayer/controlBoxV01HAL.h"

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

ISR(USART0_RX_vect)
{
	buffer[writePointer] = UDR0;

	if (writePointer >= (BUFFERSIZE - 1)) {
		writePointer = 0;
	}
	else { writePointer++; }
	
	state = 1;	/* change state / start evaluation */
}

ISR(USART1_RX_vect)
{
	bufferU1[writePointerU1] = UDR1;
	state = 1;	/* change state / start evaluation */

	if(writePointerU1 >= (BUFFERSIZE - 1))
		writePointerU1 = 0;
	else writePointerU1++;
}

void bus_setVariable(uint8_t _varID, uint16_t _varValue) {
	switch (_varID)
	{
		case statusCodeID:
			statusCode = _varValue;
		break;
		//////////////////////////////////////////////////////////////////////////
		case bounds1ID:
			bounds[0] = _varValue;
		break;
		case bounds2ID:
			bounds[1] = _varValue;
		break;
		case bounds3ID:
			bounds[2] = _varValue;
		break;
		case bounds4ID:
			bounds[3] = _varValue;
		break;
		case bounds5ID:
			bounds[4] = _varValue;
		break;
		case bounds6ID:
			bounds[5] = _varValue;
		break;
		case bounds7ID:
			bounds[6] = _varValue;
		break;
		//////////////////////////////////////////////////////////////////////////
		case voltages1ID:
			voltages[0] = _varValue;
		break;
		case voltages2ID:
			voltages[1] = _varValue;
		break;
		case voltages3ID:
			voltages[2] = _varValue;
		break;
		case voltages4ID:
			voltages[3] = _varValue;
		break;
		case voltages5ID:
			voltages[4] = _varValue;
		break;
		case voltages6ID:
			voltages[5] = _varValue;
		break;
		//////////////////////////////////////////////////////////////////////////
		case voltageDiv1ID:
			voltageDiv[0] = _varValue;
		break;
		case voltageDiv2ID:
			voltageDiv[1] = _varValue;
		break;
		case voltageDiv3ID:
			voltageDiv[2] = _varValue;
		break;
		case voltageDiv4ID:
			voltageDiv[3] = _varValue;
		break;
		//////////////////////////////////////////////////////////////////////////
		case sensorValueID:
			sensorValue = _varValue;
		break;
		//////////////////////////////////////////////////////////////////////////
		case temperatureID:
			temperature = _varValue;
		break;
		//////////////////////////////////////////////////////////////////////////
		case brightnessID:
			brightness = _varValue;
		break;
		case lightmodeID:
			lightmode = _varValue;
		break;
		//////////////////////////////////////////////////////////////////////////
		default:
			/* set intern errorCode */
			errorCode = 0x01;
		break;
	}
}

uint16_t bus_getVariable(uint8_t _varID) {
	uint16_t _varValue = 0;
	switch (_varID)
	{
		case statusCodeID:
			_varValue = statusCode;
		break;
		//////////////////////////////////////////////////////////////////////////
		case bounds1ID:
			_varValue = bounds[0];
		break;
		case bounds2ID:
			_varValue = bounds[1];
		break;
		case bounds3ID:
			_varValue = bounds[2];
		break;
		case bounds4ID:
			_varValue = bounds[3];
		break;
		case bounds5ID:
			_varValue = bounds[4];
		break;
		case bounds6ID:
			_varValue = bounds[5];
		break;
		case bounds7ID:
			_varValue = bounds[6];
		break;
		//////////////////////////////////////////////////////////////////////////
		case voltages1ID:
			_varValue = voltages[0];
		break;
		case voltages2ID:
			_varValue = voltages[1];
		break;
		case voltages3ID:
			_varValue = voltages[2];
		break;
		case voltages4ID:
			_varValue = voltages[3];
		break;
		case voltages5ID:
			_varValue = voltages[4];
		break;
		case voltages6ID:
			_varValue = voltages[5];
		break;
		//////////////////////////////////////////////////////////////////////////
		case voltageDiv1ID:
			_varValue = voltageDiv[0];
		break;
		case voltageDiv2ID:
			_varValue = voltageDiv[1];
		break;
		case voltageDiv3ID:
			_varValue = voltageDiv[2];
		break;
		case voltageDiv4ID:
			_varValue = voltageDiv[3];
		break;
		//////////////////////////////////////////////////////////////////////////
		case sensorValueID:
			_varValue = sensorValue;
		break;
		//////////////////////////////////////////////////////////////////////////
		case temperatureID:
			_varValue = temperature;
		break;
		//////////////////////////////////////////////////////////////////////////
		case brightnessID:
			_varValue = brightness;
		break;
		case lightmodeID:
			_varValue = lightmode;
		break;
		//////////////////////////////////////////////////////////////////////////
		default:
			/* set intern errorCode */
			errorCode = 0x01;
		break;
	}
	return _varValue;
}

void bus_sendDeviceInformation(void) {
	/* add device information */
	frame[0] = statusCode;

	frame[1] = (uint8_t)(bounds[0] >> 8);
	frame[2] = (uint8_t)bounds[0];
	frame[3] = (uint8_t)(bounds[1] >> 8);
	frame[4] = (uint8_t)bounds[1];
	frame[5] = (uint8_t)(bounds[2] >> 8);
	frame[6] = (uint8_t)bounds[2];
	frame[7] = (uint8_t)(bounds[3] >> 8);
	frame[8] = (uint8_t)bounds[3];
	frame[9] = (uint8_t)(bounds[4] >> 8);
	frame[10] = (uint8_t)bounds[4];
	frame[11] = (uint8_t)(bounds[5] >> 8);
	frame[12] = (uint8_t)bounds[5];
	frame[13] = (uint8_t)(bounds[6] >> 8);
	frame[14] = (uint8_t)bounds[6];

	frame[15] = (uint8_t)(voltages[0] >> 8);
	frame[16] = (uint8_t)voltages[0];
	frame[17] = (uint8_t)(voltages[1] >> 8);
	frame[18] = (uint8_t)voltages[1];
	frame[19] = (uint8_t)(voltages[2] >> 8);
	frame[20] = (uint8_t)voltages[2];
	frame[21] = (uint8_t)(voltages[3] >> 8);
	frame[22] = (uint8_t)voltages[3];
	frame[23] = (uint8_t)(voltages[4] >> 8);
	frame[24] = (uint8_t)voltages[4];
	frame[25] = (uint8_t)(voltages[5] >> 8);
	frame[26] = (uint8_t)voltages[5];

	frame[27] = (uint8_t)(voltageDiv[0] >> 8);
	frame[28] = (uint8_t)voltageDiv[0];
	frame[29] = (uint8_t)(voltageDiv[1] >> 8);
	frame[30] = (uint8_t)voltageDiv[1];
	frame[31] = (uint8_t)(voltageDiv[2] >> 8);
	frame[32] = (uint8_t)voltageDiv[2];
	frame[33] = (uint8_t)(voltageDiv[3] >> 8);
	frame[34] = (uint8_t)voltageDiv[3];

	frame[35] = (uint8_t)sensorValue;
	frame[36] = (uint8_t)(sensorValue >> 8);

	frame[37] = (uint8_t)temperature;
	frame[38] = (uint8_t)(temperature >> 8);

	frame[39] = (uint8_t)brightness;

	frame[40] = (uint8_t)lightmode;
	
	USART1_sendStringWL(frame, 64);
}

void bus_process() {
	if (flag == 6 && (((writePointer - readPointer + BUFFERSIZE) % BUFFERSIZE) > 0))
	{
		temp += buffer[readPointer];

		frame[2] += ((temp + 1) >> 8);
		frame[3] = (temp + 1);

		/* send frame to the next device */
		USART1_sendStringWL(frame, 9);
		/* increase count */
		length = (temp * 5);

		/* increase readPointer (consider step over) */
		if (readPointer >= (BUFFERSIZE - 1)) {
			readPointer = 0;
		}
		else { readPointer++; }

		flag = 7;
	}

	if (flag == 1 || flag == 2 || flag == 3 || flag == 4 || flag == 5 || flag == 7)
	{
		while ((((writePointer - readPointer + BUFFERSIZE) % BUFFERSIZE) > 0) && length > 0)
		{
			if (flag == 3) {
				frame[6 - length] = buffer[readPointer];
			}
			else { USART1_sendChar(buffer[readPointer]); }

			/* increase readPointer (consider step over) */
			if (readPointer >= (BUFFERSIZE - 1)) {
				readPointer = 0;
			}
			else { readPointer++; }

			length--;
		}
	}


	if (flag == 1) {
		goto specialquery1;
	}
	if (flag == 2) {
		goto specialquery2;
	}
	if (flag == 3) {
		goto controldevice1;
	}
	if (flag == 4) {
		goto controldevice2;
	}
	if (flag == 5) {
		goto controldevice3;
	}
	if (flag == 6 || flag == 7) {
		goto standardquery1;
	}


	if (((writePointer - readPointer + BUFFERSIZE) % BUFFERSIZE) > 2)
	{
		if ((buffer[readPointer]&0xF0) == START)
		{
			/* lower 4-bits represent mode */
			mode = (buffer[readPointer]&0x0F);
			/* increase readPointer (consider step over) */
			if (readPointer >= (BUFFERSIZE - 1)) {
				readPointer = 0;				
			}
			else { readPointer++; }

			switch (mode)
			{
				case MODEADR: /* addressing */
					/* first 3-bit include toolID */
					if (((buffer[readPointer]&0xE0) >> 5) == toolID)	// if toolID matches
					{
						/* when the received toolID matches intern toolID */
						temp = ((uint16_t)(buffer[readPointer]&0x1F) << 4);
						/* increase readPointer (consider step over) */
						if (readPointer >= (BUFFERSIZE - 1)) {
							readPointer = 0; 
						}
						else { readPointer++; }
						/* store received address */
						address = temp + (buffer[readPointer] >> 4);

						/* create frame for next device */
						frame[0] = (START + MODEADR);
						frame[1] = (toolID << 5) + (uint8_t)((address + 1) >> 4);
						frame[2] = ((uint8_t)((address + 1) << 4) + STOP);
					}
					else	// when toolID does not match
					{
						/* recreate frame for next device */
						frame[0] = (START + MODEADR);
						frame[1] = buffer[readPointer];
						/* increase readPointer (consider step over) */
						if (readPointer >= (BUFFERSIZE - 1)) {
							readPointer = 0;
						}
						else { readPointer++; }
						frame[2] = buffer[readPointer];
					}
					/* send frame */
					USART1_sendStringWL(frame, 3);

					/* reset readPointer (consider step over) */
					if (readPointer >= (BUFFERSIZE - 1)) {
						readPointer = 0;
					}
					else { readPointer++; }
				break;

			//////////////////////////////////////////////////////////////////////////

				case MODESTD:
					if (((buffer[readPointer]&0xE0) >> 5) == toolID)
					{
						/* when the received toolID matches intern toolID */
						varID = (buffer[readPointer] << 3);
						/* increase readPointer (consider step over) */
						if (readPointer >= (BUFFERSIZE - 1)) {
							readPointer = 0;
						}
						else { readPointer++; }
						/* store received varID */
						varID += (buffer[readPointer] >> 5);

						temp = ((buffer[readPointer]&0x1F) << 8);

						/* reset readPointer (consider step over) */
						if (readPointer >= (BUFFERSIZE - 1)) {
							readPointer = 0;
						}
						else { readPointer++; }

						/* create frame for next device */
						frame[0] = START + MODESTD;
						frame[1] = (toolID << 5) + (uint8_t)(varID >> 3);
						frame[2] = (varID << 5);

						/* add device packet */
						frame[4] = deviceSTART + MODEDEV;
						frame[5] = (toolID << 5) + (uint8_t)(address >> 4);
						frame[6] = (uint8_t)(address << 4);
						/* get variable in dependency to varID */
						varValue = bus_getVariable(varID);
						frame[6] += (uint8_t)(varValue >> 12);
						frame[7] = (uint8_t)(varValue >> 4);
						frame[8] = (varValue << 4) + deviceSTOP;


						/* receive send incoming device packets */
						flag = 6;
						length = 1;

						standardquery1:
						if (length > 0) {
							return;
						}
						flag = 0;
						/* finish frame */
						USART1_sendChar(STOP);
					}
					
				break;

			//////////////////////////////////////////////////////////////////////////

				case MODESPE:
					/* verify toolID */
					if (((buffer[readPointer]&0xE0) >> 5) == toolID)
					{
						/* when the received toolID matches intern toolID */
						temp = ((buffer[readPointer]&0x1F) << 4);
						/* increase readPointer (consider step over) */
						if (readPointer >= (BUFFERSIZE - 1)) {
							readPointer = 0; 
						}
						else { readPointer++; }
						/* store received address */
						temp += (buffer[readPointer] >> 4);

						/* reset readPointer (consider step over) */
						if (readPointer >= (BUFFERSIZE - 1)) {
							readPointer = 0;
						}
						else { readPointer++; }

						/* create frame for next device */
						frame[0] = START + MODESPE;
						frame[1] = (toolID << 5) + (uint8_t)(temp >> 4);
						frame[2] = (uint8_t)(temp << 4);
						/* send frames to the next device */
						USART1_sendStringWL(frame, 3);

						/* verify address */
						if (temp == address)
						{
							bus_sendDeviceInformation();
						}
						else
						{
							/* receive send 63 BYTES */
							flag = 1;
							length = 63;
											
							specialquery1:
							if (length > 0) {
								return;
							}
							flag = 0;
						}
						/* finish frame */
						USART1_sendChar(STOP);
					}
					else
					{
						frame[0] = START + MODESPE;
						frame[1] = buffer[readPointer];
						/* increase readPointer (consider step over) */
						if (readPointer >= (BUFFERSIZE - 1))
							readPointer = 0;
						else readPointer++;
						frame[2] = buffer[readPointer];
						/* reset readPointer (consider step over) */
						if (readPointer >= (BUFFERSIZE - 1))
							readPointer = 0;
						else readPointer++;
						USART1_sendStringWL(frame, 3);

						flag = 2;
						length = 63;
										
						specialquery2:
						if (length > 0) {
							return;
						}
						flag = 0;
						/* finish frame */
						USART1_sendChar(STOP);
					}
				break;

			//////////////////////////////////////////////////////////////////////////

				case MODETST:
				break;

			//////////////////////////////////////////////////////////////////////////

				case MODECTR:
					/* verify toolID */
					if (((buffer[readPointer]&0xE0) >> 5) == toolID)
					{
						/* when the received toolID matches intern toolID */
						temp = ((buffer[readPointer]&0x1F) << 4);
						/* increase readPointer (consider step over) */
						if (readPointer >= (BUFFERSIZE - 1)) {
							readPointer = 0;
						}
						else { readPointer++; }
						/* store received address */
						temp += (buffer[readPointer] >> 4);

						frame[0] = START + MODECTR;
						frame[1] = (toolID << 5) + (uint8_t)(temp >> 4);
						frame[2] = buffer[readPointer];

						/* reset readPointer (consider step over) */
						if (readPointer >= (BUFFERSIZE - 1)) {
							readPointer = 0;
						}
						else { readPointer++; }

						if (temp == 0 || temp == address)
						{
							flag = 3;
							length = 3;
							
							controldevice1:
							if (length > 0) {
								return;
							}
							flag = 0;

							/* get varID & varValue from frame */
							varID = ((frame[2]&0x0F) << 4) + ((frame[3]&0xF0) >> 4);

							varValue = ((frame[3]&0x0F) << 12);
							varValue += (frame[4] << 4);
							varValue += (frame[5] >> 4);

							/* set variable in dependency of varID */
							bus_setVariable(varID, varValue);

							/* send frames to the next device */
							USART1_sendStringWL(frame, 6);
						}
						else
						{
							USART1_sendStringWL(frame, 3);

							flag = 4;
							length = 3;

							controldevice2:
							if (length > 0) {
								return;
							}
							flag = 0;
						}
					}
					else
					{
						frame[0] = START + MODECTR;
						frame[1] = buffer[readPointer];
						/* increase readPointer (consider step over) */
						if (readPointer >= (BUFFERSIZE - 1))
							readPointer = 0;
						else readPointer++;
						frame[2] = buffer[readPointer];
						USART1_sendStringWL(frame, 3);

						/* reset readPointer (consider step over) */
						if (readPointer >= (BUFFERSIZE - 1))
							readPointer = 0;
						else readPointer++;
						
						flag = 5;
						length = 3;

						controldevice3:
						if (length > 0) {
							return;
						}
						flag = 0;
					}
				break;
			}
		}
		else {
			if (readPointer >= (BUFFERSIZE - 1)) {
				readPointer = 0;
			}
			else { readPointer++; }
		}
	}
}
