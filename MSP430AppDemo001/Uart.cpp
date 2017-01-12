#include "Uart.h"

Uart::Uart(void)
{
}

Uart::~Uart(void)
{
}

void Uart::Configure(unsigned divider, unsigned char firstModulation, unsigned char secondModulation)
{
	UCA0CTL1 = UCSSEL_2;
	UCA0BR0 = divider & 0xFF;
	UCA0BR1 = divider >> 8;
	UCA0MCTL = ((firstModulation  & 0xF) << 4) | 
	           ((secondModulation & 0x7) << 1);
	UCA0CTL1 &= ~UCSWRST;	
}

bool Uart::HasData()
{
	return IFG2 & UCA0RXIFG;
}

unsigned char Uart::Read()
{
	while (!(IFG2 & UCA0RXIFG));
	return UCA0RXBUF;	
}

void Uart::Write(unsigned char byte)
{
	while (!(IFG2 & UCA0TXIFG));
	UCA0TXBUF = byte;	
}
