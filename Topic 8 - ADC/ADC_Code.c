#include<lpc214x.h> // To define all Special Function Registers (SFRs) - Address Mapping   
#include"delay.h" // Add delay.h file to the project folder (directory) and then, compile the project.

void adc_ini(void); // Function to Configure ADC
unsigned int val;

// Main Function:
int main()
{
	PINSEL2 = 0X00000000; // Configure functionality of Port1 as GPIO 
	IODIR1 = 0XFFFFFFFF; // Configure direction of Port1 as output (LED)
	adc_ini();
	
	// Infinite Loop (An embedded program does not stop):
	while(1)
	{
		AD0CR = 0x00200700; // Set ADC Clock as VPB or (PCLK)/8, Disable BURST Mode, Set Resolution as 10 Bit in 11 Clock Cycles, and Activate ADC Module
		AD0CR |= 0x00000008; // Select ADC Channel 3 (AD0.3), i.e., Control Register (Bits 7:0)
		AD0CR |= (1<<24); // Start the Conversion now, i.e., START = 001 (Bits 26:24)
		while(!(AD0GDR & 0x80000000)); // Wait for ADC Conversion to Complete (Global Data Register), i.e., DONE = 1 (Bit 31)
		val = (AD0GDR >> 6)& 0x3FF; // Read ADC Data Register, i.e., RESULT = 10 Bit Data (15:6)
		IOPIN1 = val << 16;	// Send Data to LED to display in Port1
		AD0CR &= 0xF8FFFFFF; // Deactivate ADC Module (No Start), i.e., START = 000 (Bits 26:24)
		delay_ms(10000); // Delay of 10 seconds (10,000 ms)
	}
}

// Function to Configure ADC:	
void adc_ini()
{
	// ADC Input Pin for ADC Channel 3:
	PINSEL1 &= 0xDFFFFFFF; // Set P0.30 Pin as AD0.3 (PINSEL1<29> = 0)
	PINSEL1 |= 0x10000000; // Set P0.30 Pin as AD0.3 (PINSEL1<28> = 0)

	PCONP |= (unsigned long)(0x00000001) << 12;	// Enable Power/Clock to ADC0, i.e., Power Control for Peripheral
}
