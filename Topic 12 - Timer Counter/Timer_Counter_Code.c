// Assume PCLK = CCLK = 60MHz; Steps to setup PCLK = CCLK in PLL are as follows:
/* Click Starup.s -> Select Configuration Wizard (Tab); Put Tick Mark in VPB Setup;
Select VPB Clock as "VPB Clock = CPU Clock"; Put Tick Mark in PLL Setup;
Select MSEL as 5 and PSEL as 2 */

#include<lpc214x.h> // To define all Special Function Registers (SFRs) - Address Mapping

#define MR0I (1<<0) // Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC.
#define MR0R (1<<1)	// Reset on MR0: the TC will be reset if MR0 matches it.
#define DELAY_MS 500 // Delay of 0.5 seconds.
#define PRESCALE 60000 // 60000 PCLK clock cycles to increment TC by 1.

void initTimer0(void); // Function to Configure Timer Counter
__irq void T0ISR(void);	// ISR should have "__irq" as the keyword

// Main Function:
int main(void)
{
	initTimer0(); // Initialize Timer0
	IO0DIR = 0xFFFFFFFF; // Configure direction of all pins on Port 0 as output
	IO0PIN = 0x0;		
	T0TCR = 0x01; // Enable timer 
	while(1); // Infinite Loop (An embedded program does not stop)
}

// Function to Configure Timer Counter:
void initTimer0(void)
{
	// Configure Timer0:
	T0CTCR = 0x0; // Timer mode: every rising PCLK edge	
	T0PR = PRESCALE - 1; //(Value in Decimal!) - Increment T0TC at every 60000 clock cycles; Count begins from zero, hence subtracting 1; 
	                     // 60000 clock cycles at 60 MHz = 1 ms	
	T0MR0 = DELAY_MS - 1; //(Value in Decimal!) Zero indexed count, hence subtracting 1			
	T0MCR = MR0I | MR0R; // Set bit 0 & bit 1 to HIGH which is to interrupt & reset TC on MR0 respectively.

	// Setup Timer0 Interrupt:
	VICVectAddr4 = (unsigned)T0ISR; // Pointer Interrupt Function (ISR)	  
	VICVectCntl4 = 0x20 | 4; // 0x20 (i.e, bit 5 = 1) to enable Vectored IRQ slot; 
	                         // 0x4 (bit[4:0]) is the source number, here its timer0 which has VIC channel mask number as 4	   	
	VICIntEnable = 0x10; // Enable timer0
			
	// Reset Timer:
	T0TCR = 0x02; 
}

// ISR should have "__irq" as the keyword:
__irq void T0ISR(void)
{
	long int regVal;
	regVal = T0IR; // Read current IR value	 		
	IO0PIN = ~IO0PIN; // Toggle the state of the pins	   
	T0IR = regVal; // Write back to IR to clear interrupt flag
	VICVectAddr = 0x0; // To signal end of interrupt execution
}
