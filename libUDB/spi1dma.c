// This file is part of MatrixPilot.
//
//    http://code.google.com/p/gentlenav/
//
// Copyright 2009-2011 MatrixPilot Team
// See the AUTHORS.TXT file for a list of authors of MatrixPilot.
//
// MatrixPilot is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MatrixPilot is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MatrixPilot.  If not, see <http://www.gnu.org/licenses/>.

#include "spi1dma.h"
#include "spi1.h"
#include "delay.h"
#include <spi.h>


static void cfgDma0SpiTx(void);
static void cfgDma1SpiRx(void);
static void cfgSPI1Master(void);

static void ProcessSpiRxSamples(unsigned int * SpiRxBuffer);

unsigned int Spi1RxBuffA[16] __attribute__((space(dma)));
unsigned int Spi1RxBuffB[16] __attribute__((space(dma)));
unsigned int Spi1TxBuffA[16] __attribute__((space(dma)));
unsigned int Spi1TxBuffB[16] __attribute__((space(dma)));


// DMA0 configuration
// Direction: Read from DMA RAM and write to SPI buffer
// AMODE: Register Indirect with Post-Increment mode
// MODE: Continuous, Ping-Pong Enabled
// IRQ: SPI
/*
void cfgDma0SpiTx(void)
{
	DMA0CON = 0x2002;					
	DMA0CNT = 15;						
	DMA0REQ = 0x00A;					

	DMA0PAD = (volatile unsigned int) &SPI1BUF;
	DMA0STA = __builtin_dmaoffset(Spi1TxBuffA);
	DMA0STB = __builtin_dmaoffset(Spi1TxBuffB);
		
	IFS0bits.DMA0IF  = 0;			// Clear DMA interrupt
	IEC0bits.DMA0IE  = 1;			// Enable DMA interrupt
	DMA0CONbits.CHEN = 1;			// Enable DMA Channel	
}

void initSPITxBuff(void)
{
	unsigned int i;

    for (i = 0; i < 16; i++)
        Spi1TxBuffA[i] = i;
}

void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void)
{
      IFS0bits.DMA0IF = 0;		// Clear the DMA0 Interrupt Flag;
}
 */

// DMA1 configuration
// Direction: Read from SPI buffer and write to DMA RAM 
// AMODE: Register Indirect with Post-Increment mode
// MODE: Continuous, Ping-Pong Enabled
// IRQ: SPI
void cfgDma1SpiRx(void)
{
//	DMA1CON = 0x0002;				// 10 = Continuous, Ping-Pong modes enabled
	DMA1CON = 0x0001;				// 01 = One-Shot, Ping-Pong modes disabled
	DMA1CONbits.SIZE = 1;			// Byte Transfer
	DMA1CONbits.NULLW = 1;			// Null data write to peripheral			



	DMA1CNT = 15;						
	DMA1REQ = 0x00A;				// Peripheral = SPI1
	DMA1REQbits.FORCE = 1;			// Force a single DMA transfer (Manual mode)

	DMA1PAD = (volatile unsigned int) &SPI1BUF;
	DMA1STA= __builtin_dmaoffset(Spi1RxBuffA);
	DMA1STB= __builtin_dmaoffset(Spi1RxBuffB);

	IFS0bits.DMA1IF  = 0;			// Clear DMA interrupt
	IEC0bits.DMA1IE  = 1;			// Enable DMA interrupt
	DMA1CONbits.CHEN = 1;			// Enable DMA Channel			
}

void cfgSpi1Master(void)
{
// Configure SPI2CON register to the following
// •	Idle state for clock is a low level (SPI1CON1bits.CKP=?)
// •	Data out on Active to Idle Edge (SPI1CON1bits.CKE=?)
// •	16-bit data transfer mode (SPI1CON1bits.MODE16=?)
// •	Enable Master mode (SPI1CON1bits.MSTEN=?)
// •	Set Primary Pre-scalar for 4:1 ratio (SPI1CON1bits.PPRE=?)
// •	Set Secondary Pre-scalar for 2:1 ratio (SPI1CON1bits.SPRE=?)
// •	Enable SDO output (SPI1CON1bits.DISSDO=?)
// •	Enable SCK output (SPI1CON1bits.DISSCK=?)
		SPI1CON1bits.CKP    = 0; 
		SPI1CON1bits.CKE    = 1; 
		SPI1CON1bits.MODE16 = 1; 
		SPI1CON1bits.MSTEN  = 1; 
		SPI1CON1bits.SPRE   = 6; 
		SPI1CON1bits.PPRE   = 2;
 		SPI1CON1bits.DISSDO = 0;
		SPI1CON1bits.DISSCK = 0;		

// •	Enable SPI module (SPI1STATbits.SPIEN=?)
		SPI1STATbits.SPIEN = 1; 

// •	Force First word after Enabling SPI
    	DMA0REQbits.FORCE = 1;
    	while (DMA0REQbits.FORCE == 1);	
}

void initSPIRxBuff(void)
{
	unsigned int i;

   	for (i = 0; i < 16; i++) {
        Spi1RxBuffA[i] = 0xDEED;
        Spi1RxBuffB[i] = 0xDEED;
	}	
}

unsigned int RxDmaBuffer = 0;

void __attribute__((interrupt, no_auto_psv)) _DMA1Interrupt(void)
{
	if (RxDmaBuffer == 0) {
		ProcessSpiRxSamples(&Spi1RxBuffA[0]);
	} else {
		ProcessSpiRxSamples(&Spi1RxBuffB[0]);
	}

	RxDmaBuffer ^= 1;

    IFS0bits.DMA1IF = 0;		// Clear the DMA0 Interrupt Flag
}

static void ProcessSpiRxSamples(unsigned int * SpiRxBuffer)
{
	/* Do something with SPI Samples */
}
