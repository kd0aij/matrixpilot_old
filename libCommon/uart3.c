/*

UART3 Driver File for PIC24.

********************************************************************************
 FileName:        uart3.c
 Dependencies:    HardwareProfile.h
 Processor:       PIC24
 Compiler:        MPLAB C30
 Linker:          MPLAB LINK30
 Company:         Microchip Technology Incorporated

Author                Date      Comment
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
KO                 12-Feb-2008  Modified to use HardwareProfile.h
KO                 11-Oct-2006  v1.0
Anton Alkhimenok   18-Oct-2005
Anton Alkhimenok   17-Feb-2009  Added UART3Char2Hex(), UART3Hex2Char(), 
									  UART3ClearError(), UART3DataReceived()
PAT				   27-Jan-2010  Added UART3GetBaudError() for dynamic checking
								of baud rate percentage error.

********************************************************************************
Software License Agreement

Microchip Technology Inc. ("Microchip") licenses to you the right to use, copy,
modify and distribute the software - including source code - only for use with
Microchip microcontrollers or Microchip digital signal controllers; provided
that no open source or free software is incorporated into the Source Code
without Microchip�s prior written consent in each instance.

The software is owned by Microchip and its licensors, and is protected under
applicable copyright laws.  All rights reserved.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, ANY CLAIMS BY THIRD PARTIES (INCLUDING
BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

********************************************************************************
*/

//#include "Compiler.h"
#include <p33Exxxx.h>
#include "../MatrixPilot/HardwareProfile.h"
#include "uart3.h"

//******************************************************************************
// Constants
//******************************************************************************

//U3BRG register value and baudrate mistake calculation

#if defined (__C30__)
    #if defined (__dsPIC33E__) || defined (__PIC24E__)
    #define BAUDRATEREG3        (((GetPeripheralClock())/(BRG_DIV3 * BAUDRATE3)) - 1)
    #else
    #define BAUDRATEREG3        (((GetSystemClock()/2)+(BRG_DIV3/2*BAUDRATE3))/BRG_DIV3/BAUDRATE3-1)
    #endif
#elif defined (__PIC32MX__)
    #define BAUDRATEREG3        ((GetPeripheralClock()+(BRG_DIV3/2*BAUDRATE3))/BRG_DIV3/BAUDRATE3-1)
#else
    #error Cannot calculate BRG value
#endif    

#if defined (__C30__)
    #if defined (__dsPIC33E__)|| defined (__PIC24E__)
    #define BAUD_ACTUAL         ((GetPeripheralClock())/(BRG_DIV3 * (BAUDRATEREG3+1)))
    #else
    #define BAUD_ACTUAL         ((GetSystemClock()/2)/BRG_DIV3/(BAUDRATEREG3+1))
    #endif
#elif defined (__PIC32MX__)
    #define BAUD_ACTUAL         (GetPeripheralClock()/BRG_DIV3/(BAUDRATEREG3+1))
#else
    #error Cannot calculate actual baud rate
#endif 

	#define BAUD_ERROR              ((BAUD_ACTUAL > BAUDRATE3) ? BAUD_ACTUAL-BAUDRATE3 : BAUDRATE3-BAUD_ACTUAL)
	#define BAUD_ERROR_PERCENT      ((BAUD_ERROR*100+BAUDRATE3/2)/BAUDRATE3)
	
#if defined (__C30__)

	#if (BAUD_ERROR_PERCENT > 3)
	    #error UART frequency error is worse than 3%
	#elif (BAUD_ERROR_PERCENT > 2)
	    #warning UART frequency error is worse than 2%
	#endif

#endif // #if defined (__C30__)

/*******************************************************************************
Function: UART3GetBaudError()

Precondition:
    None.

Overview:
    This routine checks the UART baud rate error percentage and returns it.

Input: None.

Output: Returns the baud rate error in percent.

*******************************************************************************/
char UART3GetBaudError()
{
    unsigned int errorPercent = 0;

	errorPercent = ((BAUD_ERROR*100+BAUDRATE3/2)/BAUDRATE3);
    return (char)errorPercent;
}


/*******************************************************************************
Function: UART3GetChar()

Precondition:
    UART3Init must be called prior to calling this routine.

Overview:
    This routine waits for a byte to be received.  It then returns that byte.

Input: None.

Output: Byte received.

*******************************************************************************/
char UART3GetChar()
{
    char Temp;

    while(IFS5bits.U3RXIF == 0);

    Temp = U3RXREG;
    IFS5bits.U3RXIF = 0;
    return Temp;
}

/*******************************************************************************
Function: UART3Init()

Precondition: None.

Overview:
    This routine sets up the UART3 module.

Input: None.

Output: None.

Notes:
    Allow the peripheral to set the I/O pin directions.  If we set the TRIS
    bits manually, then when we disable the UART, the shape of the stop bit
    changes, and some terminal programs have problems.
*******************************************************************************/
void UART3Init()
{
    U3BRG = BAUDRATEREG3;
    U3MODE = 0;
    U3MODEbits.BRGH = BRGH3;
    U3STA = 0;
    U3MODEbits.UARTEN = 1;
    U3STAbits.UTXEN = 1;
    IFS5bits.U3RXIF = 0;
    
    #if defined (__PIC32MX__)
        U3STAbits.URXEN = 1;
    #endif
}

/*******************************************************************************
Function: UART3IsPressed()

Precondition:
    UART3Init must be called prior to calling this routine.

Overview:
    This routine checks to see if there is a new byte in UART reception buffer.

Input: None.

Output:
    0 : No new data received.
    1 : Data is in the receive buffer

*******************************************************************************/
char UART3IsPressed()
{
    if(IFS5bits.U3RXIF == 1)
        return 1;
    return 0;
}

/*******************************************************************************
Function: UART3PrintString( char *str )

Precondition:
    UART3Init must be called prior to calling this routine.

Overview:
    This function prints a string of characters to the UART.

Input: Pointer to a null terminated character string.

Output: None.

*******************************************************************************/
void UART3PrintString( char *str )
{
    unsigned char c;

    while( (c = *str++) )
        UART3PutChar(c);
}

/*******************************************************************************
Function: UART3PutChar( char ch )

Precondition:
    UART3Init must be called prior to calling this routine.

Overview:
    This routine writes a character to the transmit FIFO, and then waits for the
    transmit FIFO to be empty.

Input: Byte to be sent.

Output: None.

*******************************************************************************/
void UART3PutChar( char ch )
{
    U3TXREG = ch;
    #if !defined(__PIC32MX__)
        Nop();
        Nop();
    #endif
    while(U3STAbits.TRMT == 0);
}

/*******************************************************************************
Function: UART3PutDec(unsigned char dec)

Precondition:
    UART3Init must be called prior to calling this routine.

Overview:
    This function converts decimal data into a string and outputs it to UART.

Input: Binary data.

Output: None.

*******************************************************************************/
void  UART3PutDec(unsigned char dec)
{
    unsigned char res;
    unsigned char printed_already = 0;

    res = dec;

    if (res/100)
    {
        UART3PutChar( res/100 + '0' );
        printed_already = 1;
    }
    res = res - (res/100)*100;

    if ((res/10) || (printed_already == 1))
    {
        UART3PutChar( res/10 + '0' );
    }
    res = res - (res/10)*10;

    UART3PutChar( res + '0' );
}

/*******************************************************************************
Function: UART3PutHex

Precondition:
    UART3Init must be called prior to calling this routine.

Overview:
    This function converts hex data into a string and outputs it to UART.

Input: Binary data.

Output: None.

*******************************************************************************/

const unsigned char CharacterArray[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
//extern const unsigned char CharacterArray[];

void UART3PutHex( int toPrint )
{
    int printVar;

    printVar = toPrint;
    toPrint = (toPrint>>4) & 0x0F;
    UART3PutChar( CharacterArray[toPrint] );

    toPrint = printVar & 0x0F;
    UART3PutChar( CharacterArray[toPrint] );

    return;
}

/*******************************************************************************
Function: UART3PutHexWord(unsigned int toPrint)

Precondition:
    UART3Init must be called prior to calling this routine.

Overview:
    This function converts hex data into a string and outputs it to UART.

Input: Binary data.

Output: None.

*******************************************************************************/
#if defined( __C30__ ) || defined( __PIC32MX__ )
void UART3PutHexWord( unsigned int toPrint )
{
    unsigned int printVar;

    printVar = (toPrint>>12) & 0x0F;
    UART3PutChar( CharacterArray[printVar] );

    printVar = (toPrint>>8) & 0x0F;
    UART3PutChar( CharacterArray[printVar] );

    printVar = (toPrint>>4) & 0x0F;
    UART3PutChar( CharacterArray[printVar] );

    printVar = toPrint & 0x0F;
    UART3PutChar( CharacterArray[printVar] );

    return;
}

void UART3PutHexDWord( unsigned long toPrint )
{
    unsigned long printVar;

    printVar = (toPrint>>28) & 0x0F;
    UART3PutChar( CharacterArray[printVar] );

    printVar = (toPrint>>24) & 0x0F;
    UART3PutChar( CharacterArray[printVar] );

    printVar = (toPrint>>20) & 0x0F;
    UART3PutChar( CharacterArray[printVar] );

    printVar = (toPrint>>16) & 0x0F;
    UART3PutChar( CharacterArray[printVar] );

    printVar = (toPrint>>12) & 0x0F;
    UART3PutChar( CharacterArray[printVar] );

    printVar = (toPrint>>8) & 0x0F;
    UART3PutChar( CharacterArray[printVar] );

    printVar = (toPrint>>4) & 0x0F;
    UART3PutChar( CharacterArray[printVar] );

    printVar = toPrint & 0x0F;
    UART3PutChar( CharacterArray[printVar] );

    return;
}

#endif

/*********************************************************************
Function: char UART3Char2Hex(char ch)

PreCondition: none

Input: ASCII to be converted

Output: number

Side Effects: none

Overview: converts ASCII coded digit into number

Note: none

********************************************************************/
char UART3Char2Hex(char ch){
  // Wrong char
  if(ch > 102)
    return 0;  
  
  // From a to f     
  if(ch > 96)
    return (ch-87);
    
  // Wrong char    
  if(ch > 70)
    return 0;
  
  // From A to F    
  if(ch > 64)
    return (ch-55);

  // Wrong char  
  if(ch > 57)
    return 0;
  
  // From 0 - 9
  if(ch > 47)
    return(ch-48);
  else
  // Wrong char
    return 0;
}

/*********************************************************************
Function: char UART3Hex2Char(char hex)

PreCondition: none

Input: number

Output: ASCII code

Side Effects: none

Overview: converts low nibble into ASCII coded digit

Note: none

********************************************************************/
char UART3Hex2Char(char hex){
char h;
  h = hex&0x0f;
  // From 0xa to 0xf
  if(h>9)
    return (h+55);
  else
    return (h+48);
}

/*********************************************************************
Function: void UART3ClrError(void)

PreCondition: none

Input: none

Output: character received

Side Effects: none

Overview: wait for character

Note: none

********************************************************************/
void UART3ClrError(void){
    // Clear error flag
    if(U3STAbits.OERR)
		U3STAbits.OERR = 0;
}

