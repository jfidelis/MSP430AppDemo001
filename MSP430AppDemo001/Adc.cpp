#include "Adc.h"


Adc::Adc(void)
{
}


Adc::~Adc(void)
{
}


void Adc::Setup()
{
	ADC10AE0 = 0;
	ADC10CTL0 &= ~ENC;
	ADC10CTL0 = SREF_1 | REFON | ADC10ON;	
}


unsigned int Adc::DoSingleMeasurement(int channelNumber)
{
	ADC10CTL0 &= ~ENC;
	ADC10CTL1 = ((channelNumber & 0xF) << 12) | ADC10DIV_7;
	ADC10CTL0 |= ENC | ADC10SC;

	while (!(ADC10CTL0 & ADC10IFG));

	return ADC10MEM;	
}
