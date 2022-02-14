#include<lpc214x.h> // To define all Special Function Registers (SFRs) - Address Mapping   

// Main Function
int main (void)
{
	// Execution Starts Here:
	PINSEL0 = 0x00000005; // Set P0.0 Pin as TxD and P0.1 Pin as RxD (UART0)
	U0LCR = 0x83; // Set 8 Bits - NO Parity - 1 Stop Bit for Transmission - DLAB = 1
	U0DLL = 97; // Set BAUD Rate as 9600 bps at 15 MHz VPB Clock (PCLK)
	U0LCR = 0x03; // Disable Access to Divisor Latches
	
	// Infinite Loop (An embedded program does not stop):
	while(1)
	{
		while(!(U0LSR & 0x20)); // Wait until UART0 is ready to send character     
		U0THR = 'a';  // Sent a character to UART Transmit Shift Register
	}                               
}
