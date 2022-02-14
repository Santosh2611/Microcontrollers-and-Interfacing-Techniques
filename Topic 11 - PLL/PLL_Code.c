#include<lpc214x.h> // To define all Special Function Registers (SFRs) - Address Mapping

// Main Function:
int main()
{
	// Steps for PLL Configuration (FOSC = 12 MHz, CCLK = 60 MHz, PCLK = 15 MHz):

	PLL0CON = 0x01; // Enable PLL and disconnect PLL from CPU and other peripherals
	PLL0CFG = 0x24; // Configure PLL Multiplier (M) and Divider (P) values from the MSEL and PSEL bits respectively
	PLL0FEED = 0xAA; PLL0FEED = 0x55; // Feed sequence for locking to desired frequency
	while( !( PLL0STAT & 0x00000400)); // Check whether the PLL0 has locked on to the desired frequency
	PLL0CON = 0x03; // Enable (again) PLL and connect the PLL to CPU
	PLL0FEED = 0xAA; PLL0FEED = 0x55; // Feed sequence fo connecting the PLL0 as system clock
	VPBDIV = 0x00; // Configure PCLK at 1/4 frequency of system clock
	while(1); // Infinite Loop (An embedded program does not stop) 

}
