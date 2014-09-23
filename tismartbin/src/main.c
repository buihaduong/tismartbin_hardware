/*
 * main.c
 *
 *  Created on: Sep 23, 2014
 *      Author: HaDuong
 */

#include "main.h"

#ifdef DEBUG
void __error__(char *pcFilename, uint32_t ui32Line) {
}
#endif

int main(void) {
	unsigned char button_val;
	unsigned char Delta;
	unsigned char Rawstate;

	//
	// Setup the system clock to run at 50 Mhz from PLL with crystal reference
	//
	SysCtlClockSet(
			SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ
					| SYSCTL_OSC_MAIN);

	//
	// Enable and configure the GPIO port for the LED operation.
	//
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(LED, RED_LED | BLUE_LED | GREEN_LED);
	GPIOPinWrite(LED, RED_LED | BLUE_LED | GREEN_LED, 0x00);

	ButtonsInit();

	//
	// Loop Forever
	//
	while (1) {
		SysCtlDelay(100000);

		button_val = ButtonsPoll(&Delta, &Rawstate);

		if (BUTTON_PRESSED(LEFT_BUTTON,button_val,Delta)) {
			isRunning = !isRunning;
			if (isRunning)
				GPIOPinWrite(LED, BLUE_LED | GREEN_LED, BLUE_LED);
			else
				GPIOPinWrite(LED, RED_LED | BLUE_LED | GREEN_LED, 0x00);
		}

		if (BUTTON_PRESSED(RIGHT_BUTTON,button_val,Delta)) {
			isCalibrating = !isCalibrating;
			if (isCalibrating)
				GPIOPinWrite(LED, BLUE_LED | GREEN_LED, GREEN_LED);
			else
				GPIOPinWrite(LED, RED_LED | BLUE_LED | GREEN_LED, 0x00);
		}
	}
}
