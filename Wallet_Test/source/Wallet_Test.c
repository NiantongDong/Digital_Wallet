/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    Wallet_Test.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include <string.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
int main(void) {

    SYSMPU_Type *base = SYSMPU;

    /* Disable SYSMPU. */
    base->CESR &= ~SYSMPU_CESR_VLD_MASK;
    CRYPTO_InitHardware();

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif
    int bufferSize = 20;
    char *inputBuffer = malloc(bufferSize * sizeof(char));

    //Flags~~~
    int entranceFlag = 0;
    int bodyFlag = 1;

    while(entranceFlag == 0 )
    {
    	PRINTF("Welcome to our WIP Wallet!\nEnter the correct Something and enter: ");

    	//inputBuffer = fgets(inputBuffer, bufferSize, stdin);

    	//inputBuffer[strcspn(inputBuffer, "\n")] = '\0';


    	scanf("%14s", inputBuffer);
    	//printf("String: %s",inputBuffer);

    	if (strcmp(inputBuffer, "Something")==0)
    	{
    		entranceFlag = 1;
    	}
    	else
    	{
    		PRINTF("Wrong! Try again.\n\n");
    	}
    }

//Make menu print into function.
    /*
     * NEED TO DO
     * Fix semi-infinite loop when input is more than 1 character. Probably change the scanf() to a fgets(), or find way to sanitise any extra input.
     * Maybe convert from string to int.
     */
    PRINTF("\nHello World, you made it!\n\n");

    while(bodyFlag){
		PRINTF("What would you like to do?\n"
				"1    See public key\n"
				"2    See private key\n"
				"3    Exit\n");

		inputBuffer = malloc(bufferSize * sizeof(char));

		PRINTF("Option: ");
		scanf("%1s", inputBuffer);


		//fgets(inputBuffer, 1, stdin);
		inputBuffer[strcspn(inputBuffer, "\n")] = 0;

		if (strncmp(inputBuffer, "1",1)==0)
		{
			PRINTF("\nEntered public key. Hmmm seems we're missing that part!\n\n");
		}
		else if (strncmp(inputBuffer, "2",1)==0)
		{
			PRINTF("\nEntered private key. Hmmm seems we're missing that part!\n\n");
		}
		else if (strncmp(inputBuffer, "3",1)==0)
		{
			PRINTF("\nEntered Exit. Goodbye!\n");
			return 0;
		}
		else
		{
			PRINTF("\nInvalid Command! Returning for now, but should take you back to menu.\n");
		}
		//char *inputBuffer = malloc(bufferSize * sizeof(char));
		//fflush(stdin);
    }
//strtoi





    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}
