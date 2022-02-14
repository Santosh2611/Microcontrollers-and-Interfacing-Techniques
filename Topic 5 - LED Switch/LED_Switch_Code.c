#include<lpc214x.h> // To define all Special Function Registers (SFRs) - Address Mapping
char switchStatus;

// Main Function:
int main (void)
{
	PINSEL0 = 0x00000000; // Configure Functionality of P0.0 and P0.1 as GPIO Port
	IO0DIR &= 0xFFFFFFFE; // Configure Direction of P0.0 as Input Pin (Switch)
	IO0DIR |= 0x00000002; // Configure Direction of P0.1 as Output Pin (LED)

	// Infinite Loop:
	while (1)
	{
		switchStatus = (IOPIN0 & 0x01);	// Check if Switch Connected to P0.0 is Pressed
		if(switchStatus == 1)
		{
			IOSET0 |= 0x00000002; // If Pressed, Switch ON LED Connected to P0.1
		} 				
		else
		{
			IOCLR0 |= 0x00000002; // Else Switch OFF LED Connected to P0.1	   	
		}	
	}
}
