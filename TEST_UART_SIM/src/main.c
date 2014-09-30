/*
 * main.c
 *
 *  Created on: Sep 23, 2014
 *      Author: HaDuong
 */

#include "main.h"
#include "temperature.h"

#ifdef DEBUG
void __error__(char *pcFilename, uint32_t ui32Line) {
}
#endif

char data[128];
int index_data;
double distance = 0.0;
double max_distance = 20;
int percentage = 0;
int oldPercentage = 0;
uint32_t tempC;

void Blink(int led, int times, int ms) {
	int i = 0;
	for (i = 0; i < times; ++i) {
		GPIOPinWrite(LED, RED_LED | BLUE_LED | GREEN_LED, led);
		delay_ms(ms);
		GPIOPinWrite(LED, RED_LED | BLUE_LED | GREEN_LED, 0x00);
		delay_ms(ms);
	}
}

int main(void) {
	unsigned char button_val;
	unsigned char Delta;
	unsigned char Rawstate;

	//
	// Setup the system clock to run at 80 Mhz from PLL with crystal reference
	//
	SysCtlClockSet(
			SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN
					| SYSCTL_XTAL_16MHZ);

	//
	// Enable and configure the GPIO port for the LED operation.
	//
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(LED, RED_LED | BLUE_LED | GREEN_LED);
	GPIOPinWrite(LED, RED_LED | BLUE_LED | GREEN_LED, 0x00);

	Blink(GREEN_LED | BLUE_LED, 5, 50);

	ButtonsInit();
	UARTInit();

	while (1) {
		SysCtlDelay(100000);

		button_val = ButtonsPoll(&Delta, &Rawstate);

		if (BUTTON_PRESSED(LEFT_BUTTON,button_val,Delta)) {
			if (SendAndCheck("AT", 1)) {
				Blink(BLUE_LED, 1, 300);
			} else {
				Blink(RED_LED, 1, 300);
			}
		}

		if (BUTTON_PRESSED(RIGHT_BUTTON,button_val,Delta)) {
			break;
		}
	}

	Blink(GREEN_LED, 1, 1000);

	ADCInit();
	InitSonar();
	SimInit();

	Blink(BLUE_LED, 1, 1000);

	//
	// Loop Forever
	//
	while (1) {
		SysCtlDelay(100000);

		button_val = ButtonsPoll(&Delta, &Rawstate);

		if (BUTTON_PRESSED(LEFT_BUTTON,button_val,Delta)) {
			GPIOPinWrite(LED, RED_LED | BLUE_LED | GREEN_LED, GREEN_LED);
			max_distance = GetDistanceSonar();
			GPIOPinWrite(LED, RED_LED | BLUE_LED | GREEN_LED, 0x00);

			if (SendAndCheck("AT", 1)) {
				Blink(BLUE_LED, 1, 300);
			} else {
				Blink(RED_LED, 1, 300);
			}
		}

		if (BUTTON_PRESSED(RIGHT_BUTTON,button_val,Delta)) {
			isRunning = !isRunning;
		}

		if (isRunning) {
			tempC = GetTemperature();
			if (tempC > 70) {
				SendData(DATA_TEMP, tempC);
				Blink(RED_LED, 3, 100);
			}

			distance = GetDistanceSonar();
			percentage = (int) floor(
					((max_distance - distance) * 100.0) / max_distance);
			if ((percentage >= 0) && (percentage <= 100)
					&& abs(percentage - oldPercentage) > 10) {
				SendData(DATA_TRASH, percentage);
				oldPercentage = percentage;
			}

			Blink(GREEN_LED, 1, 10);
		}
	}
}
