/*
 * temperature.c
 *
 *  Created on: Sep 30, 2014
 *      Author: HaDuong
 */

#include "temperature.h"

void ADCInit() {
	//Configure pin for ADC
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);	//Enable Peripheral Port
	GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_1);	//ADC pin

	//Configure ADC module
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);		//Enable Module ADC0
	//Configure the hardware oversampling for the ADC - 4 conversions at once
	ADCHardwareOversampleConfigure(ADC0_BASE, 64);
	//Processor ADC trigger
	ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH6);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_CH6);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_CH6);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 3,
			ADC_CTL_END | ADC_CTL_CH6 | ADC_CTL_IE);
	ADCSequenceEnable(ADC0_BASE, 1);		//Enable ADC
	ADCIntEnable(ADC0_BASE, 1);		//Enable ADC Interrupt
}

uint32_t GetTemperature() {
	uint32_t ui32ADC0Value[4];
	uint32_t ui32TempAvg;
	uint32_t ui32TempValueC;

	ADCIntClear(ADC0_BASE, 1);
	ADCProcessorTrigger(ADC0_BASE, 1);

	while (!ADCIntStatus(ADC0_BASE, 1, false)) {
	}

	ADCSequenceDataGet(ADC0_BASE, 1, ui32ADC0Value);
	ui32TempAvg = (ui32ADC0Value[0] + ui32ADC0Value[1] + ui32ADC0Value[2]
			+ ui32ADC0Value[3] + 2) / 4;
	ui32TempValueC = ((3300 * ui32TempAvg) / 4096) / 10;

	return ui32TempValueC;
}
