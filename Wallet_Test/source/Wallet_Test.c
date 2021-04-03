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
#include <stdlib.h>
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
char* key_return(FILE *fp);


int main(void) {

    SYSMPU_Type *base = SYSMPU;

    /* Disable SYSMPU. */
    base->CESR &= ~SYSMPU_CESR_VLD_MASK;
    //CRYPTO_InitHardware();

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

    //Flags
    int entranceFlag = 0;
    int bodyFlag = 1;

    /* Keys and file management*/
    char output_buffer[128];

    char *public_key =
    		"-----BEGIN PUBLIC KEY-----"
    		"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAv6Dmm3NvbVDz2Nh+wwc+"
    		"YOjGLDSuSu940LMiyIkfOXRPd2AhUjV44MW98eVlDrG885dqBG/Hr0JVKufXAAEi"
    		"4atyf3epluU9gcWbdEHA9dPwnNntMb4L4H8TPMju91nrTHE5uI+Sz9QtwaCTF9Ll"
    		"FotM0+PT+0YVLDjsb8phVg9nPyHUrror6Uy9blAl7JMfUg6T6kflqPZoQuA6L2uk"
    		"T7XO1v+5k8B4g7sRIbwtBfwD7cYZDLDMXFSqJKn9Ilg6lzHKUdQc+wn7WlSqDANf"
    		"qHec4Ph4AxExW4/V7u80XI/mcT+6c0rgna58AvOwPCtzMVAd2hu0eY3DIhhXNYC5"
    		"NwIDAQAB"
    		"-----END PUBLIC KEY-----";

    char *private_key =
    		"-----BEGIN RSA PRIVATE KEY-----"
    		"MIIEowIBAAKCAQEAv6Dmm3NvbVDz2Nh+wwc+YOjGLDSuSu940LMiyIkfOXRPd2Ah"
    		"UjV44MW98eVlDrG885dqBG/Hr0JVKufXAAEi4atyf3epluU9gcWbdEHA9dPwnNnt"
    		"Mb4L4H8TPMju91nrTHE5uI+Sz9QtwaCTF9LlFotM0+PT+0YVLDjsb8phVg9nPyHU"
    		"rror6Uy9blAl7JMfUg6T6kflqPZoQuA6L2ukT7XO1v+5k8B4g7sRIbwtBfwD7cYZ"
    		"DLDMXFSqJKn9Ilg6lzHKUdQc+wn7WlSqDANfqHec4Ph4AxExW4/V7u80XI/mcT+6"
    		"c0rgna58AvOwPCtzMVAd2hu0eY3DIhhXNYC5NwIDAQABAoIBAEZCm2rxtzAwl0ex"
    		"kUC2vjNQBaEdq64EAZsboyw9wnoRYDWXxH/c5TYcqpkvj48Esg/qO0/nICLtQkbZ"
    		"/GWfBQgTEYcU+9Q8twGGz4mftj0r+TO5X5N2Z+pnDUmjLqL4kCJV/WDjG2QiGqi8"
    		"1FHO3HoYlxG1nfqqZobxVBdk761ak6Pzbiw74q77RWxjlBEtgLC2E67eDqJKSUdI"
    		"VvkFNile+uY99KjQHkiY0Hn5vx1nLSlIKMi5rRsdE+jYgQGI02/fTkWASp/XJixe"
    		"fNoUGgsTtvPBTJoghqm3A83N11Y8WYv9CPkVBBm6AwHeo6BmJqQ9dzudbHTzaooV"
    		"ZMPLBQkCgYEA7WvwML+44lxJHlJk+OGw1EsV8T57DM6kVrECN/KsnfQKvBA4vbKI"
    		"OVApDzRRVLcLEoArXO33EHGwBl6flOvMM8VSzSEkPBc6BF7I9dMvWDOGJIrKs6Kl"
    		"YLq75ay6/+zhot9peohvdsXsWHWtG49h72SS47DSBmVsvHQFxsIJ2cUCgYEAzp+g"
    		"+J/LH9JDqDt5pO6n7tksTVhv4HH9JCTZ3Jf2RgIfIgUKIsTBUUtsUwQC/aX4Cwuu"
    		"l8KFzyuTdzAziEUaEu+3Dpx3KAYb/XcZ83pp2iTyTP3zuK9VGnIgBbpZvJSL0pJq"
    		"qweGzJBH5mvxmc9GnzUyzt22pW81qvz0M9tfgssCgYBtZ+fvDuorpUssZduRtK6/"
    		"pTofSSN6615fdIIJNhLFVsf7kZ4UDEkp3/6LuxgfaZn4lIdm82F+emUbCk+PWHlp"
    		"Aez+Cd+gsTNTADqqzP5sLpIKFMsDrFd5E5Oyar5hYM85NqpshKKYoOwgd1ml8ZS3"
    		"tCjcM4cU23gX/38J8DCJ4QKBgD5f4fAsDN2mU9ZNXgN0KC3qUX1n3R4cSxbGKR52"
    		"oVmw+kUC0HR+gP1Rj3ngFCcOGzr6Y9JcXpiTxwiL/IJ+mchtpQ08Hpxue7SgZ60g"
    		"nyPDU4H6h8CQ7Vf2a8RO5RgQn8UJfjnzI7ZNN+dPXrfX4rHdFWFtfN2kHMdpZS7i"
    		"YorRAoGBAOzJGmaIAgZoy4dl1wW7cQhtFHUQjn/AXhk3r6HZryfbqTQ2UjIzB9Cp"
    		"4J5cMvACdleZaeDF+UpW1iu2E6aqGD9/zARQrTKrR2L/AHETqQHwKUtubO2b9G2q"
    		"p+gYN2bV4VO9iL1H0TqqUGy/DK9iPAgigeP7/fy+Xa9v+Wy1EhzY"
    		"-----END RSA PRIVATE KEY-----";


    while(entranceFlag == 0 )
    {
    	PRINTF("Welcome to our WIP Wallet!\nEnter the correct Something and enter: ");

//Add section for probing our public key? To show visitors.

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
    PRINTF("\nHello World, you made it! \n\n");

    while(bodyFlag){
		PRINTF("What would you like to do?\n"
				"1    See public key\n"
				"2    See private key\n"
				"3    Sign a message\n"		//Same kind of encoding with our private key to send a message out.
				"4    Read an input message\n"	//When we recieve a message, we decrpyt it using our private key.
				"5    Exit\n");

		inputBuffer = malloc(bufferSize * sizeof(char));

		PRINTF("Option: ");
		scanf("%1s", inputBuffer);

//Create a "Hello World" message from wallet (encrypted through our private key) that the world can read with our public key. Validates identity.
		inputBuffer[strcspn(inputBuffer, "\n")] = 0;

		if (strncmp(inputBuffer, "1",1)==0)
		{
			PRINTF("\nEntered public key. \n\n");
		    //FILE *fp_public = fopen("49742dfdf5-public.pem.key", "r");
		    FILE *fp_public = fopen("./test.txt", "r");
		     if(fp_public == NULL) {
		    	 PRINTF("Unable to open file!\nUsing hard-coded value for now:\n%s\n\n",public_key);
		     }
		     else
		     {
				 while(fgets(output_buffer, sizeof(output_buffer), fp_public) != NULL) {
					 PRINTF("Printing public key\n");
				 }
				 fclose(fp_public);
		     }
		}
		else if (strncmp(inputBuffer, "2",1)==0)
		{
			PRINTF("\nEntered private key. \n\n");
		    //FILE *fp_private = fopen("49742dfdf5-private.pem.key", "r");
		    FILE *fp_private = fopen("./test.txt", "r");
		    if(fp_private == NULL) {
		    	 PRINTF("Unable to open file!\nUsing hard-coded value for now:\n%s\n\n",private_key);
		    }
		    else
		    {
				 while(fgets(output_buffer, sizeof(output_buffer), fp_private) != NULL) {
					 PRINTF("Printing public key\n");
				 }
				 fclose(fp_private);
		    }
		}
		else if (strncmp(inputBuffer, "3",1)==0)
		{

			PRINTF("\nEntered private key:");

		}
		else if (strncmp(inputBuffer, "4",1)==0)
		{
			PRINTF("\nEntered Exit. Goodbye!\n");
			return 0;
		}
		else
		{
			PRINTF("\nInvalid Command! Returning for now, but should take you back to menu.\n");
		}
    }




    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
}


