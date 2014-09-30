/*
 * uart_sim.c
 *
 *  Created on: Sep 27, 2014
 *      Author: HaDuong
 */

#include "uart_sim.h"

void UARTInit() {
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

	//
	// Enable port PC6 for UART3 U3RX
	//
	GPIOPinConfigure(GPIO_PC6_U3RX);
	GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6);

	//
	// Enable port PC7 for UART3 U3TX
	//
	GPIOPinConfigure(GPIO_PC7_U3TX);
	GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_7);

	UARTConfigSetExpClk(UART3_BASE, SysCtlClockGet(), 115200,
			(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
	UARTEnable(UART3_BASE);
}

void SimInit() {
	SendCommand("AT");
	GetDataSIML(9);
	delay_ms(500);

	SendCommand("AT+CIPSHUT");
	GetDataSIML(22);
	delay_ms(500);

	SendCommand("AT+CIPSTART=\"TCP\",\"robotbase.ddns.net\",\"8888\"");
	GetDataSIML(62);
	delay_ms(500);
}

void UARTPuts(uint32_t UART_Base, const char *s) {
	while (*s) {
		UARTCharPut(UART_Base, *s++);
	}
}

void GetDataSIM() {
	while (!UARTCharsAvail(UART3_BASE))
		;
	index_data = 0;
	char c = UARTCharGet(UART3_BASE);
	while (UARTCharsAvail(UART3_BASE)) {
		data[index_data] = c;
		c = UARTCharGetNonBlocking(UART3_BASE);
		index_data++;
	}
}

void GetDataSIML(int lenght) {
	while (!UARTCharsAvail(UART3_BASE))
		;
	index_data = 0;
	char c;
	while (lenght > 0) {
		c = UARTCharGet(UART3_BASE);
		data[index_data] = c;
		index_data++;
		lenght--;
	}
}

void SendCommand(const char *command) {
	UARTPuts(UART3_BASE, command);
	UARTCharPut(UART3_BASE, 0x0d);
}

int SendAndCheck(const char *command, int times) {
	SendCommand(command);
	GetDataSIM();
	int i = 0;
	for (i = 0; i < index_data - 1; ++i)
		if ((data[i] == 'O') && (data[i + 1] == 'K')) {
			times--;
			if (times == 0)
				return 1;
		}
	return 0;
}

void SendData(int DATA_TYPE, int data) {
	char stringData[8];
	if (DATA_TYPE == DATA_TRASH)
		usprintf(stringData,"r%d",data);
	else if (DATA_TYPE == DATA_TEMP)
		usprintf(stringData,"n%d",data);

	SendCommand("AT+CIPSEND");
	delay_s(1);
	SendCommand(stringData);
	UARTCharPut(UART3_BASE, 0x1a);
}
