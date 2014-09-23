/*
 * main.h
 *
 *  Created on: Sep 23, 2014
 *      Author: HaDuong
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "drivers/buttons.h"
#include "delay.h"
#include "sonar.h"

#define	LED	GPIO_PORTF_BASE
#define RED_LED   GPIO_PIN_1
#define BLUE_LED  GPIO_PIN_2
#define GREEN_LED GPIO_PIN_3

bool isRunning = false;
bool isCalibrating = false;

#endif /* MAIN_H_ */
