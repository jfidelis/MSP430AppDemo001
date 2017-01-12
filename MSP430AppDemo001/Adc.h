#include <msp430.h>
#pragma once
class Adc
{
public:
	Adc(void);
	~Adc(void);
	
	void Setup();
	unsigned int DoSingleMeasurement(int channelNumber);
	
};

