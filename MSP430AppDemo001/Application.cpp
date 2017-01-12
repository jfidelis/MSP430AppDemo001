#include <msp430.h>
#include "Uart.h"
#include "Adc.h"
#include <stdio.h>

Uart uart;
Adc adc;

extern "C" int putchar(int ch)
{
	uart.Write(ch);
}

void Delay()
{
	long counter = 0;
	while (counter++ < 5000)
		asm("nop");
}

void MainLoop()
{
	WDTCTL = WDTPW | WDTHOLD;
	
	DCOCTL = 0;
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;	

	P1SEL |= BIT1 | BIT2;
	P1SEL2 |= BIT1 | BIT2;
		
	uart.Configure(104, 1, 0); 
	adc.Setup();
	
	unsigned CAL_ADC_15T30 = *((unsigned *)(0x10DA + 0x08));
	unsigned CAL_ADC_15T85 = *((unsigned *)(0x10DA + 0x0A));	
	
	for (;;)
	{
		//unsigned char byte = uart.Read();
		//uart.Write(byte + 1);
		
		const int iterations = 16384;

		unsigned long sum = 0;
		for (int i = 0; i < iterations; i++)
			sum += adc.DoSingleMeasurement(0xA);

		unsigned average = sum / iterations;

		int tempCx10 = ((long) average - CAL_ADC_15T30) * (85 - 30) * 10 / (CAL_ADC_15T85 - CAL_ADC_15T30) + 300;

		printf("%d.%d C\r\n", 
			tempCx10 / 10, 
			tempCx10 % 10, 
			(unsigned)(sum / iterations));
		
		Delay();
	}
}

int main()
{
	MainLoop();
}