#include<lpc214x.h> // To define all Special Function Registers (SFRs) - Address Mapping
#include<stdio.h> // Declares functions that deal with standard I/O
#include<stdint.h> // Declare sets of integer types having specified widths
#include<stdlib.h> // General purpose standard library of C programming language 

// Variable Delay Function:
void delay_ms(uint16_t j)
{
    uint16_t x, i;

	// Loop to Generate 1 ms Delay with CCLK = 60 MHz:
	for(i=0;i<j;i++)
	{
    	for(x=0;x<6000;x++);
	}
}

// Display Character Using LCD Command Write Function:
void LCD_CMD(char command)
{
	// Upper Nibble of Command:
	IO0PIN = ( (IO0PIN & 0xFFFF00FF) | ((command & 0xF0)<<8) ); // Split and move MSB 4-Bits of LCD command
	IO0SET = 0x00000040; // EN = 1
	IO0CLR = 0x00000030; // Set LCD_RS = 0 & LCD_RW = 0
	delay_ms(5); // Call Delay Function
	IO0CLR = 0x00000040; // EN = 0
	delay_ms(5); // Call Delay Function

	// Lower Nibble of Command:
	IO0PIN = ( (IO0PIN & 0xFFFF00FF) | ((command & 0x0F)<<12) ); // Split and move LSB 4-Bits of LCD command
	IO0SET = 0x00000040; // EN = 1
	IO0CLR = 0x00000030; // Set LCD_RS = 0 & LCD_RW = 0
	delay_ms(5); // Call Delay Function
	IO0CLR = 0x00000040; // EN = 0
	delay_ms(5); // Call Delay Function	
}

// Function to Configure LCD:
void LCD_INIT(void)
{
	IO0DIR = 0x0000FFF0; // Set P0.12 to P0.15 LCD Data (D4 to D7); P0.4, 5, 5 as RS, RW and EN as output
	delay_ms(20); // Call Delay Function
	LCD_CMD(0x02); // Initialize Cursor to Home Position

	LCD_CMD(0x28); // Function Set: 4-Bit, 2 Line, 5*7 Dots
	LCD_CMD(0x0C); // Display ON, Cursor OFF, Blink OFF
	LCD_CMD(0x06); // Set the Entry Mode (Cursor Increment, Display Shift OFF)

	LCD_CMD(0x01); // Clear LCD display; Also, clear DDRAM content
	delay_ms(5); // Call Delay Function
	LCD_CMD(0x80); // Set DDRAM address or cursor position on display to first line
}

// Display String Using Data Write Function: 
void LCD_STRING (char* msg)
{
	uint8_t i = 0;
	while(msg[i]!=0)
	{
		IO0PIN = ( (IO0PIN & 0xFFFF00FF) | ((msg[i] & 0xF0)<<8) ); // Split and move MSB 4-Bits of LCD command
		IO0SET = 0x00000050; // Set LCD_RS = 1 & EN = 1
		IO0CLR = 0x00000020; // Set LCD_RW = 0
		delay_ms(2); // Call Delay Function
		IO0CLR = 0x00000040; // EN = 0
		delay_ms(5); // Call Delay Function

		IO0PIN = ( (IO0PIN & 0xFFFF00FF) | ((msg[i] & 0x0F)<<12) ); // Split and move LSB 4-Bits of LCD command
		IO0SET = 0x00000050; // Set LCD_RS = 1 & EN = 1
		IO0CLR = 0x00000020; // Set LCD_RW = 0
		delay_ms(2); // Call Delay Function
		IO0CLR = 0x00000040; // EN = 0
		delay_ms(5); // Call Delay Function

		i++;
	}
}

// Display Character Using Data Write Function: 
void LCD_CHAR (char msg)
{
		IO0PIN = ( (IO0PIN & 0xFFFF00FF) | ((msg & 0xF0)<<8) ); // Split and move MSB 4-Bits of LCD command
		IO0SET = 0x00000050; // Set LCD_RS = 1 & EN = 1
		IO0CLR = 0x00000020; // Set LCD_RW = 0
		delay_ms(2); // Call Delay Function
		IO0CLR = 0x00000040; // EN = 0
		delay_ms(5); // Call Delay Function

		IO0PIN = ( (IO0PIN & 0xFFFF00FF) | ((msg & 0x0F)<<12) ); // Split and move LSB 4-Bits of LCD command
		IO0SET = 0x00000050; // Set LCD_RS = 1 & EN = 1
		IO0CLR = 0x00000020; // Set LCD_RW = 0
		delay_ms(2); // Call Delay Function
		IO0CLR = 0x00000040; // EN = 0
		delay_ms(5); // Call Delay Function
}

char val_j[3];

// Main Function:
int main(void)
{
	uint8_t j = 0;
		
	LCD_INIT(); // Call Function to Configure LCD
	LCD_STRING("Good Day!");
	LCD_CMD(0xC0); // Set DDRAM address or cursor position on display to second line 
	LCD_STRING("Val of j is:");

	for(j=0;j<10;j++)
	{		
		sprintf(val_j,"%d ",j);
		LCD_STRING(val_j);	
		delay_ms(100); // Call Delay Function
		LCD_CMD(0xCC);
	}

	return 0;
}
