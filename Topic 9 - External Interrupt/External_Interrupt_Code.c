#include<lpc214x.h> // To define all Special Function Registers (SFRs) - Address Mapping
//#include "ext_int.h"

// Variable Delay Function:
void delay(int count)
{
  int j=0, i=0;		  
  for(j=0;j<count;j++)
  {
    // At 60 Mhz, the below loop introduces a delay of 10 us.
    for(i=0;i<35;i++);
  }
}

// ISR should have "__irq" as the keyword:  
void Ext_ISR() __irq
{
	// Connect PushButton Switch to P0.14 (EINT1); Don't connect to P0.3 which is also EINT1:
	IOSET1 |= 1<<26; // Switch ON LED connected to P1.26
	delay(10000); // Call delay() function 
    IOCLR1 |= 1<<26; // Switch OFF LED connected to P1.26
	EXTINT |= 0x2; // Clear EINT1 Interrupt Flag Bit; EXTINT <1> = 1	
	VICVectAddr = 0; // This register should be written near the end of an ISR, to update the priority hardware.
}

// Function to Configure External Interrupt:
void eint1_init()
{
  // External Interrupt Registers:
  EXTMODE = 0x2; // Configure Edge Sensitive/Level Sensitive Interrupt for EINT1; EXTMODE <1> = 1 (Edge Sensitive)
  EXTPOLAR &= 0xFFFFFFFD; // Configure Rising/Falling Edge Sensitive Interrupt for EINT1; EXTPOLAR <1> = 0 (Falling)

  // First make Bit 28 & 29 as '0', then make Bit 29 as '1':
  PINSEL0 = (PINSEL0 & 0xCFFFFFFF) | (1 << 29);	// Configure P0.14 as EINT; PINSEL0 <29:28> = 10

  // VIC Registers:
  VICIntSelect &= 0xFFFF7FFF; // Configure EINT1 (Interrupt Number 15) as FIQ/IRQ; VICIntSelect <15> = 0 (IRQ)
  VICVectAddr5 = (unsigned int)Ext_ISR; // Configure ISR Vector Address to VIC IRQ Slot
  VICVectCntl5 = 15; // Configure the Interrupt Number of Interrupt Request assigned to Vectored IRQ Slot (IRQ Slot 5)
  VICVectCntl5 |= 1<<5; // Enable Vectored IRQ Slot (IRQ Slot 5); VICVectCntl5 <5> = 1
  VICIntEnable = 1<<15; // Enable EINT1 Interrupt; VICIntEnable <15> = 1

  // External Interrupt Registers:
  EXTINT |= 0x2; // Clear EINT1 Interrupt Flag Bit; EXTINT <1> = 1
}

// Main Function:
int main (void) 
{
	IODIR1 |= 1<<26; // Configure P1.26 as output to connect LED
  	eint1_init(); // Call EINT1	function

	// Infinite Loop (An embedded program does not stop):
	while (1);
}
