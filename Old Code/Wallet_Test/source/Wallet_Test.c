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

/* Encryption Library */
#include "mbedtls/pk.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"



/* FreeRTOS Libraries */
#include "FreeRTOS.h"

/*
 * @brief   Application entry point.
 */
char* key_return(FILE *fp);


/* Keys and file management*/
unsigned char *public_key =
		/*"-----BEGIN PUBLIC KEY-----"
		"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAv6Dmm3NvbVDz2Nh+wwc+"
		"YOjGLDSuSu940LMiyIkfOXRPd2AhUjV44MW98eVlDrG885dqBG/Hr0JVKufXAAEi"
		"4atyf3epluU9gcWbdEHA9dPwnNntMb4L4H8TPMju91nrTHE5uI+Sz9QtwaCTF9Ll"
		"FotM0+PT+0YVLDjsb8phVg9nPyHUrror6Uy9blAl7JMfUg6T6kflqPZoQuA6L2uk"
		"T7XO1v+5k8B4g7sRIbwtBfwD7cYZDLDMXFSqJKn9Ilg6lzHKUdQc+wn7WlSqDANf"
		"qHec4Ph4AxExW4/V7u80XI/mcT+6c0rgna58AvOwPCtzMVAd2hu0eY3DIhhXNYC5"
		"NwIDAQAB\0"
		"-----END PUBLIC KEY-----";*/

"-----BEGIN PUBLIC KEY-----MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAv6Dmm3NvbVDz2Nh+wwc+YOjGLDSuSu940LMiyIkfOXRPd2AhUjV44MW98eVlDrG885dqBG/Hr0JVKufXAAEi4atyf3epluU9gcWbdEHA9dPwnNntMb4L4H8TPMju91nrTHE5uI+Sz9QtwaCTF9LlFotM0+PT+0YVLDjsb8phVg9nPyHUrror6Uy9blAl7JMfUg6T6kflqPZoQuA6L2ukT7XO1v+5k8B4g7sRIbwtBfwD7cYZDLDMXFSqJKn9Ilg6lzHKUdQc+wn7WlSqDANfqHec4Ph4AxExW4/V7u80XI/mcT+6c0rgna58AvOwPCtzMVAd2hu0eY3DIhhXNYC5NwIDAQAB-----END PUBLIC KEY-----";




unsigned char *private_key =
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
  //  int bufferSize = 20;
    int ret = 0;
    //char *inputBuffer = malloc(bufferSize * sizeof(char));
    unsigned char *message = "Hello World!";
    size_t message_length = strlen(message);

    PRINTF("Size of message: %zu \n", message_length);

    //Flags
   // int entranceFlag = 0;
    //int bodyFlag = 1;

    /* Keys and file management*/
    *public_key++ = '\0';		//\0 added as requirement from pk_parse function: https://tls.mbed.org/api/pk_8h.html#ade680bf8e87df7ccc3bb36b52e43972b
    							//Commenting this section out allows print statements to continue, but with incorrect string.

    /* Entropy Initilisation
     *
     * https://tls.mbed.org/kb/how-to/add-a-random-generator
     * */
    mbedtls_entropy_context entropy;
    mbedtls_entropy_init( &entropy );

    /* Creating Random Generator */

    mbedtls_ctr_drbg_context ctr_drbg;
    char *personalization = "Oh lordy will this work?";

    mbedtls_ctr_drbg_init( &ctr_drbg );

    ret = mbedtls_ctr_drbg_seed( &ctr_drbg , mbedtls_entropy_func, &entropy,
                     (const unsigned char *) personalization,
                     strlen( personalization ) );
    if( ret != 0 )
    {
        return -1;
    }

    /* RSA Initialization */


    mbedtls_pk_context pk;				//Getting hardfault here?
    mbedtls_pk_init( &pk );

    PRINTF("Before public key parse:\n");
    /* Reading RSA Public Key */
    //if( ( ret = mbedtls_pk_parse_public_keyfile(&pk, "49742dfdf5-public.pem.key")) != 0 ) This is a wrapper for the below function. IO isn't working, so using hard coded string.
    if( ( ret = mbedtls_pk_parse_public_key(&pk, public_key,strlen(public_key)+1)) != 0 )
    {
        printf( " failed\n  ! mbedtls_pk_parse_public_keyfile returned -0x%04x\n", -ret );
        return -1;
    }
    PRINTF("After public key parse:\n");

/* RSA Encryption
 *
 *
 *  The result is in buf, with the actual size you should copy out in olen.
 * */
    unsigned char buf[MBEDTLS_MPI_MAX_SIZE];
    size_t olen = 0;

    /*
     * Calculate the RSA encryption of the data.
     */
    printf( "\n  . Generating the encrypted value" );
    fflush( stdout );

    if( ( ret = mbedtls_pk_encrypt( &pk, message, message_length,
                                    buf, &olen, sizeof(buf),
                                    mbedtls_ctr_drbg_random, &ctr_drbg ) ) != 0 )
    {
        printf( " failed\n  ! mbedtls_pk_encrypt returned -0x%04x\n", -ret );
        return -1;
    }
    printf( "\nEncrypted Message:\n%s\n",buf );

//
///* Body loop for menu */
//
//    while(entranceFlag == 0 )
//    {
//    	PRINTF("Welcome to our WIP Wallet!\nEnter the correct Something and enter: ");
//
//
//    	scanf("%14s", inputBuffer);
//
//    	if (strcmp(inputBuffer, "Something")==0)
//    	{
//    		entranceFlag = 1;
//    	}
//    	else
//    	{
//    		PRINTF("Wrong! Try again.\n\n");
//    	}
//    }
//
//
//    PRINTF("\nHello World, you made it! \n\n");
//
//    while(bodyFlag){
//		PRINTF("What would you like to do?\n"
//				"1    See public key\n"
//				"2    See private key\n"
//				"3    Sign a message\n"		//Same kind of encoding with our private key to send a message out.
//				"4    Read an input message\n"	//When we recieve a message, we decrpyt it using our private key.
//				"5    Exit\n");
//
//		inputBuffer = malloc(bufferSize * sizeof(char));
//
//		PRINTF("Option: ");
//		scanf("%1s", inputBuffer);
//
//
//		if (strncmp(inputBuffer, "1",1)==0)
//		{
//			PRINTF("\nEntered public key. \n\n");
//		}
//		else if (strncmp(inputBuffer, "2",1)==0)
//		{
//			PRINTF("\nEntered private key. \n\n");
//		}
//		else if (strncmp(inputBuffer, "3",1)==0)
//		{
//			PRINTF("\nEntered private key:");
//
//		}
//		else if (strncmp(inputBuffer, "5",1)==0)
//		{
//			PRINTF("\nEntered Exit. Goodbye!\n");
//			return 0;
//		}
//		else
//		{
//			PRINTF("\nInvalid Command! Returning for now, but should take you back to menu.\n");
//		}
//    }
//
//
//

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


