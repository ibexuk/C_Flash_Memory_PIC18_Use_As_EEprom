/*
Provided by IBEX UK LTD http://www.ibexuk.com
Electronic Product Design Specialists
RELEASED SOFTWARE

The MIT License (MIT)

Copyright (c) IBEX UK Ltd, http://ibexuk.com

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
//Visit http://www.embedded-code.com/source-code/memory/flash-memory-ics/microchip-pic18-flash-program-memory-as-eeprom-driver for more information
//
//Project Name: Using PIC18 flash program memory as eeprom to store non volatile data for devices without eeeprom memory



#include "main.h"					//Global data type definitions (see https://github.com/ibexuk/C_Generic_Header_File )
#define MEM_FLASH_C
#include "mem-flash.h"




//********************************************
//********************************************
//********** FLASH MEMORY READ PAGE **********
//********************************************
//********************************************
void flash_memory_read_page (DWORD start_address, BYTE *p_buffer, WORD length)
{
	BYTE count;
	DWORD_VAL address;
	
	address.val = start_address;

	TBLPTRU = address.v[2];
	TBLPTRH = address.v[1];
	TBLPTRL = address.v[0];

	for (count = 0; count < length; count++)
	{
		_asm
		//tblrd*+
		TBLRDPOSTINC			//TBLRD, TBLRDPOSTDEC, TBLRDPOSTINC, TBLRDPREINC
		//dw	0xffff				//(Silicon Bug Fix)
		_endasm

		*p_buffer++ = TABLAT;
	}

}



//*********************************************
//*********************************************
//********** FLASH MEMORY WRITE PAGE **********
//*********************************************
//*********************************************
//For the PIC18F45J50 the erase block size is 1024 bytes and the write block size is 64 bytes.			//<<<<<<<<<<<<<<<< CHECK THIS IS TRUE FOR FOR YOUR PIC DEVICE
//
//Bear in mind that the last program memory block will be used by the debugger so typically an application will use the block before to store NV memory.
//This function will erase the block and then write as many bytes as requested
void flash_memory_write_page (DWORD start_address, BYTE *p_buffer, WORD length)
{
	WORD write_count;
	BYTE block_count;
	DWORD_VAL address;
	
	address.val = start_address;
	
	DISABLE_INT;

	//-----------------------
	//----- ERASE BLOCK -----
	//-----------------------
	//Set address
	TBLPTRU = address.v[2];
	TBLPTRH = address.v[1];
	TBLPTRL = address.v[0];

	//DO ERASE
	//EECON1bits.EEPGD = 1;		//Point to program flash memory not eeprom
	//EECON1bits.CFGS = 0;		//Access program memory not configuration registers
	EECON1bits.WREN = 1;		//Enable write to memory
	EECON1bits.FREE = 1;		//Enable Erase operation

	EECON2 = 0x55;				//Do the write enable sequence
	EECON2 = 0xaa;
	EECON1bits.WR = 1;			//Start erase (CPU stall)
	Nop();


	write_count = 0;
	while (write_count < length)
	{
		//----- WRITE DATA -----
		//Set address
		TBLPTRU = address.v[2];
		TBLPTRH = address.v[1];
		TBLPTRL = address.v[0];

		for (block_count = 0; block_count < FLASH_WRITE_BLOCK_SIZE; block_count++)
		{
			//----------------------------
			//----- WRITE NEXT BLOCK -----
			//----------------------------
			if (write_count < length)
			{
				TABLAT = *p_buffer++;
				write_count++;
			}
			else
			{
				TABLAT = 0xff;
			}

			_asm
			//tblwt*
			TBLWTPOSTINC			//TBLWT, TBLWTPOSTDEC, TBLWTPOSTINC, TBLWTPREINC
			_endasm
		}

		//Set address back to start of block
		TBLPTRU = address.v[2];
		TBLPTRH = address.v[1];
		TBLPTRL = address.v[0];

		//----- BURN BLOCK -----
		//EECON1bits.EEPGD = 1;		//Point to program flash memory not eeprom
		//EECON1bits.CFGS = 0;		//Access program memory not configuration registers
		EECON1bits.WPROG = 0;
		EECON1bits.WREN = 1;		//Enable writing

		EECON2 = 0x55;				//Do the write enable sequence
		EECON2 = 0xaa;
		EECON1bits.WR = 1;			//Start erase (CPU stall)
		Nop();

		EECON1bits.WREN = 0;		//Disable writing
		
		address.val += FLASH_WRITE_BLOCK_SIZE;
	}

	ENABLE_INT;
}




