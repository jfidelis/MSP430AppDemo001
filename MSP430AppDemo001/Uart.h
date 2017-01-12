#include <msp430.h>
#pragma once
class Uart
{
public:
	Uart(void);
	~Uart(void);
	void Configure(unsigned divider, unsigned char firstModulation, unsigned char secondModulation);	
	bool HasData();
	unsigned char Read();
	void Write(unsigned char byte);
};

