/*
 * temperature.h
 *
 *  Created on: Sep 30, 2014
 *      Author: HaDuong
 */

#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"
#include "driverlib/adc.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"

void ADCInit();
uint32_t GetTemperature();

#endif /* TEMPERATURE_H_ */
