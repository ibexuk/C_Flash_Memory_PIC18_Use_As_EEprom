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


//*********************************
//*********************************
//********** USAGE NOTES **********
//*********************************
//*********************************

//Include this header file in any .c files within your project from which you wish to use it's functions.

/*
Example usage:
	BYTE my_array[100]
 
	//----- READ NON VOLATILE MEMORY -----
	flash_memory_read_page(NON_VOLATILE_PROG_MEMORY_START_ADDRESS, &my_array[0], 100);

	//----- WRITE NON VOLATILE MEMORY -----
	flash_memory_write_page (NON_VOLATILE_PROG_MEMORY_START_ADDRESS, &my_array[0], 100);
*/



//*****************************
//*****************************
//********** DEFINES **********
//*****************************
//*****************************
#ifndef MEM_FLASH_C_INIT		//Do only once the first time this file is used
#define	MEM_FLASH_C_INIT


//FLASH NV MEMORY
//PIC18F45J50 has no eeprom so we use a block of flash program memory.
//Debugger uses part of last block, so we need to use prior block.
//Device address range: 0x0000 - 0x7FFF
//Erase blocks are 1024 bytes (0x400)
#define	NON_VOLATILE_PROG_MEMORY_START_ADDRESS	0x7800			//<<<<<<<<<<<<<<<< SET FOR YOUR PIC DEVICE
#define	FLASH_WRITE_BLOCK_SIZE					64				//Writes to program memory occur in blocks of # bytes for thsi device

#endif


//*******************************
//*******************************
//********** FUNCTIONS **********
//*******************************
//*******************************
#ifdef MEM_FLASH_C
//-----------------------------------
//----- INTERNAL ONLY FUNCTIONS -----
//-----------------------------------



//-----------------------------------------
//----- INTERNAL & EXTERNAL FUNCTIONS -----
//-----------------------------------------
//(Also defined below as extern)
void flash_memory_read_page (DWORD start_address, BYTE *p_buffer, WORD length);
void flash_memory_write_page (DWORD start_address, BYTE *p_buffer, WORD length);


#else
//------------------------------
//----- EXTERNAL FUNCTIONS -----
//------------------------------
extern void flash_memory_read_page (DWORD start_address, BYTE *p_buffer, WORD length);
extern void flash_memory_write_page (DWORD start_address, BYTE *p_buffer, WORD length);


#endif




//****************************
//****************************
//********** MEMORY **********
//****************************
//****************************
#ifdef MEM_FLASH_C
//--------------------------------------------
//----- INTERNAL ONLY MEMORY DEFINITIONS -----
//--------------------------------------------




//--------------------------------------------------
//----- INTERNAL & EXTERNAL MEMORY DEFINITIONS -----
//--------------------------------------------------
//(Also defined below as extern)


#else
//---------------------------------------
//----- EXTERNAL MEMORY DEFINITIONS -----
//---------------------------------------



#endif






