/*
 * uart_sim.h
 *
 *  Created on: Sep 27, 2014
 *      Author: HaDuong
 */

#ifndef UART_SIM_H_
#define UART_SIM_H_

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "driverlib/uart.h"
#include "delay.h"
#include "utils/ustdlib.h"
#include <math.h>

#define DATA_TRASH	0
#define	DATA_TEMP	1

extern char data[128];
extern int index_data;

void UARTInit();
void UARTPuts();
void GetDataSIM();
void GetDataSIML(int lenght);
void SendCommand(const char *command);
int SendAndCheck(const char *command,int times);
void SimInit();
void SendData(int DATA_TYPE, int data);

#endif /* UART_SIM_H_ */
