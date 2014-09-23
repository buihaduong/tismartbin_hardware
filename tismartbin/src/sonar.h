/*
 * sonar.h
 *
 *  Created on: Sep 23, 2014
 *      Author: HaDuong
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "delay.h"

#ifndef SONAR_H_
#define SONAR_H_

#define SONAR	GPIO_PORTE_BASE
#define	TRIGGER	GPIO_PIN_3
#define ECHO	GPIO_PIN_2

void InitSonar(void);
double GetDistanceSonar(void);

#endif /* SONAR_H_ */
