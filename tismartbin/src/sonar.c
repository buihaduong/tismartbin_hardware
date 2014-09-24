/*
 * sonar.c
 *
 *  Created on: Sep 23, 2014
 *      Author: HaDuong
 */

#include "sonar.h"

void InitSonar() {
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	GPIOPinTypeGPIOOutput(SONAR, TRIGGER);
	GPIOPinTypeGPIOInput(SONAR, ECHO);
	GPIOPinWrite(SONAR, TRIGGER, 0x00);
}

double GetDistanceSonar() {
	int32_t EchoPin = 0;
	double time = 0.0;
	double dist = 0.0;

	int32_t breakCount = 0;

	GPIOPinWrite(SONAR, TRIGGER, 0xff);
	delay_us(20);
	GPIOPinWrite(SONAR, TRIGGER, 0x00);

	EchoPin = GPIOPinRead(SONAR, ECHO);
	while (!EchoPin) {
		EchoPin = GPIOPinRead(SONAR, ECHO);
		breakCount++;
		if (breakCount > 5000)
			break;
	}

	if (breakCount > 5000)
		return -1;

	breakCount = 0;

	while (EchoPin) {
		time = time + 1.0;
		//delay_us(1);
		EchoPin = GPIOPinRead(SONAR, ECHO);
		if (breakCount > 5000)
			break;
	}

	if (breakCount > 5000)
		return -1;

	dist = time / 14; // TODO : Calibrate sonar sensor
	return dist;
}
