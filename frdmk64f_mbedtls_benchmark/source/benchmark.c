/*
 *  Benchmark demonstration program
 *
 *  Copyright (C) 2006-2016, ARM Limited, All Rights Reserved
 *  SPDX-License-Identifier: Apache-2.0
 *  Copyright 2017 NXP. Not a Contribution
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <mbedtls/pk.h>
#include "mbedtls/ctr_drbg.h"
#include "fsl_rnga.h"
#include <mbedtls/base64.h>
#include "mbedtls/entropy.h"

#if defined(MBEDTLS_PLATFORM_C)

#if defined(FREESCALE_KSDK_BM)

#include "mbedtls/version.h"
#include <stdio.h>
#include "fsl_debug_console.h"
#include "fsl_clock.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#if defined(MBEDTLS_NXP_SSSAPI)
#include "sssapi_mbedtls.h"
#else
#include "ksdk_mbedtls.h"
#endif

#define mbedtls_printf PRINTF
#define mbedtls_snprintf snprintf
#define mbedtls_exit(x) \
    do                  \
    {                   \
    } while (1)
#define mbedtls_free free
#define fflush(x) \
    do            \
    {             \
    } while (0)

#else
#include "mbedtls/platform.h"
#endif
#else
#include <stdio.h>
#include <stdlib.h>
#define mbedtls_exit       exit
#define mbedtls_printf     printf
#define mbedtls_snprintf   snprintf
#define mbedtls_free       free
#define mbedtls_exit            exit
#define MBEDTLS_EXIT_SUCCESS    EXIT_SUCCESS
#define MBEDTLS_EXIT_FAILURE    EXIT_FAILURE
#endif

#if !defined(MBEDTLS_TIMING_C) && !defined(FREESCALE_KSDK_BM)
int main(void)
{
    mbedtls_printf("MBEDTLS_TIMING_C not defined.\n");
    return( 0 );
}
#else

#include <string.h>
#include <stdlib.h>

#include "mbedtls/timing.h"

#include "mbedtls/md4.h"
#include "mbedtls/md5.h"
#include "mbedtls/ripemd160.h"
#include "mbedtls/sha1.h"
#include "mbedtls/sha256.h"
#include "mbedtls/sha512.h"

#include "mbedtls/arc4.h"
#include "mbedtls/des.h"
#include "mbedtls/aes.h"
#include "mbedtls/aria.h"
#include "mbedtls/blowfish.h"
#include "mbedtls/camellia.h"
#include "mbedtls/chacha20.h"
#include "mbedtls/gcm.h"
#include "mbedtls/ccm.h"
#include "mbedtls/chachapoly.h"
#include "mbedtls/cmac.h"
#include "mbedtls/poly1305.h"

#include "mbedtls/havege.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/hmac_drbg.h"

#include "mbedtls/rsa.h"
#include "mbedtls/dhm.h"
#include "mbedtls/ecdsa.h"
#include "mbedtls/ecdh.h"

#include "mbedtls/error.h"

#if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C)
#include "mbedtls/memory_buffer_alloc.h"
#endif

#include "fsl_device_registers.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define CORE_CLK_FREQ CLOCK_GetFreq(kCLOCK_CoreSysClk)

/*
 * For heap usage estimates, we need an estimate of the overhead per allocated
 * block. ptmalloc2/3 (used in gnu libc for instance) uses 2 size_t per block,
 * so use that as our baseline.
 */
#define MEM_BLOCK_OVERHEAD  ( 2 * sizeof( size_t ) )

/*
 * Size to use for the alloc buffer if MEMORY_BUFFER_ALLOC_C is defined.
 */
#define HEAP_SIZE       (1u << 16)  // 64k

#define BUFSIZE         1024
#define HEADER_FORMAT   "  %-24s :  "
#define TITLE_LEN       25

#define OPTIONS                                                         \
    "md4, md5, ripemd160, sha1, sha256, sha512,\n"                      \
    "arc4, des3, des, camellia, blowfish, chacha20,\n"                  \
    "aes_cbc, aes_gcm, aes_ccm, aes_ctx, chachapoly,\n"                 \
    "aes_cmac, des3_cmac, poly1305\n"                                   \
    "havege, ctr_drbg, hmac_drbg\n"                                     \
    "rsa, dhm, ecdsa, ecdh.\n"

#if defined(MBEDTLS_ERROR_C)
#define PRINT_ERROR                                                     \
        mbedtls_strerror( ret, ( char * )tmp, sizeof( tmp ) );          \
        mbedtls_printf( "FAILED: %s\n", tmp );
#else
#define PRINT_ERROR                                                     \
        mbedtls_printf( "FAILED: -0x%04x\n", -ret );
#endif

#define TIME_AND_TSC(TITLE, CODE)                                                                        \
    do                                                                                                   \
    {                                                                                                    \
        uint32_t ii, jj;                                                                                 \
        uint64_t tsc1, tsc2;                                                                             \
        int ret = 0;                                                                                     \
                                                                                                         \
        mbedtls_printf(HEADER_FORMAT, TITLE);                                                            \
        fflush(stdout);                                                                                  \
                                                                                                         \
        benchmark_mbedtls_set_alarm(1);                                                                  \
        tsc1 = benchmark_mbedtls_timing_hardclock();                                                     \
        for (ii = 1; ret == 0 && !benchmark_mbedtls_timing_alarmed; ii++)                                \
        {                                                                                                \
            ret = CODE;                                                                                  \
            benchmark_mbedtls_poll_alarm();                                                              \
        }                                                                                                \
                                                                                                         \
        tsc2 = benchmark_mbedtls_timing_hardclock();                                                     \
        for (jj = 0; ret == 0 && jj < 1024; jj++)                                                        \
        {                                                                                                \
            ret = CODE;                                                                                  \
        }                                                                                                \
                                                                                                         \
        if (ret != 0)                                                                                    \
        {                                                                                                \
            PRINT_ERROR;                                                                                 \
        }                                                                                                \
        else                                                                                             \
        {                                                                                                \
            mbedtls_printf("%6.2f KB/s,  %6.2f cycles/byte\r\n",                                         \
                           (ii * BUFSIZE / 1024) / (((float)(tsc2 - tsc1)) / CLOCK_GetCoreSysClkFreq()), \
                           (((float)(benchmark_mbedtls_timing_hardclock() - tsc2)) / (jj * BUFSIZE)));   \
        }                                                                                                \
    } while (0)

#if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C) && defined(MBEDTLS_MEMORY_DEBUG)

#define MEMORY_MEASURE_INIT                                             \
    size_t max_used, max_blocks, max_bytes;                             \
    size_t prv_used, prv_blocks;                                        \
    mbedtls_memory_buffer_alloc_cur_get( &prv_used, &prv_blocks );      \
    mbedtls_memory_buffer_alloc_max_reset( );

#define MEMORY_MEASURE_PRINT( title_len )                               \
    mbedtls_memory_buffer_alloc_max_get( &max_used, &max_blocks );      \
    for( ii = 12 - (title_len); ii != 0; ii-- ) mbedtls_printf( " " );  \
    max_used -= prv_used;                                               \
    max_blocks -= prv_blocks;                                           \
    max_bytes = max_used + MEM_BLOCK_OVERHEAD * max_blocks;             \
    mbedtls_printf( "%6u heap bytes", (unsigned) max_bytes );

#else
#define MEMORY_MEASURE_INIT
#define MEMORY_MEASURE_PRINT( title_len )
#endif

#define TIME_PUBLIC(TITLE, TYPE, CODE)                                                                                \
    do                                                                                                                \
    {                                                                                                                 \
        uint32_t ii;                                                                                                  \
        uint64_t tsc;                                                                                                 \
        int ret;                                                                                                      \
        MEMORY_MEASURE_INIT;                                                                                          \
                                                                                                                      \
        mbedtls_printf(HEADER_FORMAT, TITLE);                                                                         \
        fflush(stdout);                                                                                               \
        benchmark_mbedtls_set_alarm(3);                                                                               \
                                                                                                                      \
        ret = 0;                                                                                                      \
        tsc = benchmark_mbedtls_timing_hardclock();                                                                   \
        for (ii = 1; !benchmark_mbedtls_timing_alarmed && !ret; ii++)                                                 \
        {                                                                                                             \
            CODE;                                                                                                     \
            benchmark_mbedtls_poll_alarm();                                                                           \
        }                                                                                                             \
                                                                                                                      \
        if (ret != 0)                                                                                                 \
        {                                                                                                             \
            PRINT_ERROR;                                                                                              \
        }                                                                                                             \
        else                                                                                                          \
        {                                                                                                             \
            mbedtls_printf("%6.2f " TYPE "/s",                                                                        \
                           ((float)ii) / ((benchmark_mbedtls_timing_hardclock() - tsc) / CLOCK_GetCoreSysClkFreq())); \
            MEMORY_MEASURE_PRINT(sizeof(TYPE) + 1);                                                                   \
            mbedtls_printf("\r\n");                                                                                   \
        }                                                                                                             \
    } while (0)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
static int myrand( void *rng_state, unsigned char *output, size_t len )
{
    size_t use_len;
    int rnd;

    if( rng_state != NULL )
        rng_state  = NULL;

    while( len > 0 )
    {
        use_len = len;
        if( use_len > sizeof(int) )
            use_len = sizeof(int);

        rnd = rand();
        memcpy( output, &rnd, use_len );
        output += use_len;
        len -= use_len;
    }

    return( 0 );
}

/*
 * Clear some memory that was used to prepare the context
 */
#if defined(MBEDTLS_ECP_C)
void ecp_clear_precomputed( mbedtls_ecp_group *grp )
{
    if( grp->T != NULL )
    {
        size_t i;
        for( i = 0; i < grp->T_size; i++ )
            mbedtls_ecp_point_free( &grp->T[i] );
        mbedtls_free( grp->T );
    }
    grp->T = NULL;
    grp->T_size = 0;
}
#else
#define ecp_clear_precomputed( g )
#endif

unsigned char buf[BUFSIZE];

typedef struct {
    char md4, md5, ripemd160, sha1, sha256, sha512,
         arc4, des3, des,
         aes_cbc, aes_gcm, aes_ccm, aes_xts, chachapoly,
         aes_cmac, des3_cmac,
         aria, camellia, blowfish, chacha20,
         poly1305,
         havege, ctr_drbg, hmac_drbg,
         rsa, dhm, ecdsa, ecdh;
} todo_list;

#if defined(FREESCALE_KSDK_BM) && !defined(MBEDTLS_TIMING_C)

static volatile uint32_t s_MsCount = 0U;
static volatile int benchmark_mbedtls_timing_alarmed;
static uint64_t s_Timeout;

/*!
 * @brief Milliseconds counter since last POR/reset.
 */
void SysTick_Handler(void)
{
    s_MsCount++;
}

static uint64_t benchmark_mbedtls_timing_hardclock(void)
{
    uint32_t currMsCount;
    uint32_t currTick;
    uint32_t loadTick;

    do
    {
        currMsCount = s_MsCount;
        currTick    = SysTick->VAL;
    } while (currMsCount != s_MsCount);

    loadTick = CLOCK_GetCoreSysClkFreq() / 1000U;
    return (((uint64_t)currMsCount) * loadTick) + loadTick - currTick;
}

static void benchmark_mbedtls_set_alarm(int seconds)
{
    benchmark_mbedtls_timing_alarmed = 0;
    s_Timeout                        = benchmark_mbedtls_timing_hardclock() + (seconds * CLOCK_GetCoreSysClkFreq());
}

static void benchmark_mbedtls_poll_alarm(void)
{
    if (benchmark_mbedtls_timing_hardclock() > s_Timeout)
    {
        benchmark_mbedtls_timing_alarmed = 1;
    }
}
#endif

static int bench_print_features(void)
{
    char *text;
    mbedtls_printf("mbedTLS version %s\r\n", MBEDTLS_VERSION_STRING);
    mbedtls_printf("fsys=%lu\r\n", ((CORE_CLK_FREQ)));
    mbedtls_printf("Using following implementations:\r\n");
#if defined(MBEDTLS_FREESCALE_LTC_SHA256)
    text = "LTC HW accelerated";
#elif defined(MBEDTLS_FREESCALE_MMCAU_SHA256)
    text = "MMCAU HW accelerated";
#elif defined(MBEDTLS_FREESCALE_LPC_SHA256)
    text = "LPC HW accelerated";
#elif defined(MBEDTLS_FREESCALE_CAU3_SHA256)
    text = "CAU3 HW accelerated";
#elif defined(MBEDTLS_FREESCALE_DCP_SHA256)
    text = "DCP HW accelerated";
#elif defined(MBEDTLS_FREESCALE_HASHCRYPT_SHA256)
    text = "HASHCRYPT HW accelerated";
#elif defined(MBEDTLS_FREESCALE_CAAM_SHA256)
    text = "CAAM HW accelerated";
#elif defined(MBEDTLS_NXP_SENTINEL200)
    text = "S200 HW accelerated";
#elif defined(MBEDTLS_NXP_SENTINEL300)
    text = "S300 HW accelerated";
#else
    text = "Software implementation";
#endif
    mbedtls_printf("  SHA: %s\r\n", text);
#if defined(MBEDTLS_FREESCALE_LTC_AES)
    text = "LTC HW accelerated";
#elif defined(MBEDTLS_FREESCALE_MMCAU_AES)
    text = "MMCAU HW accelerated";
#elif defined(MBEDTLS_FREESCALE_LPC_AES)
    text = "LPC HW accelerated";
#elif defined(MBEDTLS_FREESCALE_CAU3_AES)
    text = "CAU3 HW accelerated";
#elif defined(MBEDTLS_FREESCALE_DCP_AES)
    text = "DCP HW accelerated";
#elif defined(MBEDTLS_FREESCALE_HASHCRYPT_AES)
    text = "HASHCRYPT HW accelerated";
#elif defined(MBEDTLS_FREESCALE_CAAM_AES)
    text = "CAAM HW accelerated";
#elif defined(MBEDTLS_NXP_SENTINEL200)
    text = "SW AES, S200 HW accelerated CCM and CMAC";
#elif defined(MBEDTLS_NXP_SENTINEL300)
    text = "SW AES, S300 HW accelerated CCM and CMAC";
#else
    text = "Software implementation";
#endif
    mbedtls_printf("  AES: %s\r\n", text);
#if defined(MBEDTLS_FREESCALE_LTC_AES_GCM)
    text = "LTC HW accelerated";
#elif defined(MBEDTLS_FREESCALE_MMCAU_AES)
    text = "MMCAU HW accelerated";
#elif defined(MBEDTLS_FREESCALE_LPC_AES_GCM)
    text = "LPC HW accelerated";
#elif defined(MBEDTLS_FREESCALE_CAU3_AES)
    text = "CAU3 HW accelerated";
#elif defined(MBEDTLS_FREESCALE_CAAM_AES)
    text = "CAAM HW accelerated";
#else
    text = "Software implementation";
#endif
    mbedtls_printf("  AES GCM: %s\r\n", text);
#if defined(MBEDTLS_FREESCALE_LTC_DES)
    text = "LTC HW accelerated";
#elif defined(MBEDTLS_FREESCALE_MMCAU_DES)
    text = "MMCAU HW accelerated";
#elif defined(MBEDTLS_FREESCALE_CAU3_DES)
    text = "CAU3 HW accelerated";
#elif defined(MBEDTLS_FREESCALE_CAAM_DES)
    text = "CAAM HW accelerated";
#else
    text = "Software implementation";
#endif
    mbedtls_printf("  DES: %s\r\n", text);
#if defined(MBEDTLS_FREESCALE_LTC_PKHA)
    text = "LTC HW accelerated";
#elif defined(MBEDTLS_FREESCALE_CAU3_PKHA)
    text = "CAU3 HW accelerated";
#elif defined(MBEDTLS_FREESCALE_CASPER_PKHA)
    text = "CASPER HW accelerated ECC256/384/521 and RSA verify";
#elif defined(MBEDTLS_FREESCALE_CAAM_PKHA)
    text = "CAAM HW accelerated";
#elif defined(MBEDTLS_NXP_SENTINEL200)
    text = "S200 HW accelerated ECDSA and ECDH";
#elif defined(MBEDTLS_NXP_SENTINEL300)
    text = "S300 HW accelerated ECDSA and ECDH";
#else
    text = "Software implementation";
#endif
    mbedtls_printf("  Asymmetric cryptography: %s\r\n", text);

    return 0;
}

/* Keys and file management*/
unsigned char *public_key =
		"-----BEGIN PUBLIC KEY-----\n"
		"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAp0Jb2UNeN0FNyFNWbqzo\n"
		"XHEyZ3BSRv0XyHwS1pmQwiIcLCo6goOv6RRutJOUee9A47pv8BDUniCV4rL6gL9n\n"
		"Up/lGBwocqkwcON9lOEQq3U53VDlm+/eY5OsBo0AfoXYugA1wj0snlCfxImtcd2J\n"
		"8MML+4vdScO90fD8Lakkjh+Ak0xhhw70QGRzsSMgkH1XJzEf0GLg3e5SDvRvXrbM\n"
		"co8ELGFB9NhVdjoBwfeAw+lhnudXaaAfhX3lyhg3Ssy0yivFei82p4FT4as8E+NB\n"
		"AQ2p+CDJSTb2GFDD3Aa4djFkPpIHWhNZNrXpl7Zl3v0Pgccwzl5GUQfLMzSGkUNk\n"
		"CQIDAQAB\n"
		"-----END PUBLIC KEY-----\n\0";

//What's the correct format??



unsigned char *private_key =
		"-----BEGIN RSA PRIVATE KEY-----\n"
		"MIIEowIBAAKCAQEAv6Dmm3NvbVDz2Nh+wwc+YOjGLDSuSu940LMiyIkfOXRPd2Ah\n"
		"UjV44MW98eVlDrG885dqBG/Hr0JVKufXAAEi4atyf3epluU9gcWbdEHA9dPwnNnt\n"
		"Mb4L4H8TPMju91nrTHE5uI+Sz9QtwaCTF9LlFotM0+PT+0YVLDjsb8phVg9nPyHU\n"
		"rror6Uy9blAl7JMfUg6T6kflqPZoQuA6L2ukT7XO1v+5k8B4g7sRIbwtBfwD7cYZ\n"
		"DLDMXFSqJKn9Ilg6lzHKUdQc+wn7WlSqDANfqHec4Ph4AxExW4/V7u80XI/mcT+6\n"
		"c0rgna58AvOwPCtzMVAd2hu0eY3DIhhXNYC5NwIDAQABAoIBAEZCm2rxtzAwl0ex\n"
		"kUC2vjNQBaEdq64EAZsboyw9wnoRYDWXxH/c5TYcqpkvj48Esg/qO0/nICLtQkbZ\n"
		"/GWfBQgTEYcU+9Q8twGGz4mftj0r+TO5X5N2Z+pnDUmjLqL4kCJV/WDjG2QiGqi8\n"
		"1FHO3HoYlxG1nfqqZobxVBdk761ak6Pzbiw74q77RWxjlBEtgLC2E67eDqJKSUdI\n"
		"VvkFNile+uY99KjQHkiY0Hn5vx1nLSlIKMi5rRsdE+jYgQGI02/fTkWASp/XJixe\n"
		"fNoUGgsTtvPBTJoghqm3A83N11Y8WYv9CPkVBBm6AwHeo6BmJqQ9dzudbHTzaooV\n"
		"ZMPLBQkCgYEA7WvwML+44lxJHlJk+OGw1EsV8T57DM6kVrECN/KsnfQKvBA4vbKI\n"
		"OVApDzRRVLcLEoArXO33EHGwBl6flOvMM8VSzSEkPBc6BF7I9dMvWDOGJIrKs6Kl\n"
		"YLq75ay6/+zhot9peohvdsXsWHWtG49h72SS47DSBmVsvHQFxsIJ2cUCgYEAzp+g\n"
		"+J/LH9JDqDt5pO6n7tksTVhv4HH9JCTZ3Jf2RgIfIgUKIsTBUUtsUwQC/aX4Cwuu\n"
		"l8KFzyuTdzAziEUaEu+3Dpx3KAYb/XcZ83pp2iTyTP3zuK9VGnIgBbpZvJSL0pJq\n"
		"qweGzJBH5mvxmc9GnzUyzt22pW81qvz0M9tfgssCgYBtZ+fvDuorpUssZduRtK6/\n"
		"pTofSSN6615fdIIJNhLFVsf7kZ4UDEkp3/6LuxgfaZn4lIdm82F+emUbCk+PWHlp\n"
		"Aez+Cd+gsTNTADqqzP5sLpIKFMsDrFd5E5Oyar5hYM85NqpshKKYoOwgd1ml8ZS3\n"
		"tCjcM4cU23gX/38J8DCJ4QKBgD5f4fAsDN2mU9ZNXgN0KC3qUX1n3R4cSxbGKR52\n"
		"oVmw+kUC0HR+gP1Rj3ngFCcOGzr6Y9JcXpiTxwiL/IJ+mchtpQ08Hpxue7SgZ60g\n"
		"nyPDU4H6h8CQ7Vf2a8RO5RgQn8UJfjnzI7ZNN+dPXrfX4rHdFWFtfN2kHMdpZS7i\n"
		"YorRAoGBAOzJGmaIAgZoy4dl1wW7cQhtFHUQjn/AXhk3r6HZryfbqTQ2UjIzB9Cp\n"
		"4J5cMvACdleZaeDF+UpW1iu2E6aqGD9/zARQrTKrR2L/AHETqQHwKUtubO2b9G2q\n"
		"p+gYN2bV4VO9iL1H0TqqUGy/DK9iPAgigeP7/fy+Xa9v+Wy1EhzY\n"
		"-----END RSA PRIVATE KEY-----\n\0";

/* Mbedtls context creation and init */
static mbedtls_ctr_drbg_context ctr_drbg;
static mbedtls_pk_context pk;
mbedtls_entropy_context entropy;

int main( int argc, char *argv[] )
{
    int i;
    unsigned char tmp[200];
    char title[TITLE_LEN];
    todo_list todo;
#if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C)
    unsigned char alloc_buf[HEAP_SIZE] = { 0 };
#endif

#if defined(FREESCALE_KSDK_BM)
    /* HW init */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();
    CRYPTO_InitHardware();

    /* Init SysTick module */
    /* call CMSIS SysTick function. It enables the SysTick interrupt at low priority */
    SysTick_Config(CLOCK_GetCoreSysClkFreq() / 1000U); /* 1 ms period */
#endif
    bench_print_features();

    /* Main Section */
    int ret = 0;
    unsigned char *message = "Hello World!";
    size_t message_length = strlen(message);
    PRINTF("Size of message: %d \r\n", message_length);

	mbedtls_ctr_drbg_init( &ctr_drbg );
	mbedtls_pk_init( &pk );
	mbedtls_entropy_init( &entropy );

    /* Randomness, needed for encryption module??? */
	mbedtls_ctr_drbg_context ctr_drbg;
	char *personalization = "oh lord let this work";

	mbedtls_ctr_drbg_init( &ctr_drbg );

	ret = mbedtls_ctr_drbg_seed( &ctr_drbg , mbedtls_entropy_func, &entropy,
	                 (const unsigned char *) personalization,
	                 strlen( personalization ) );
	if( ret != 0 )
	{
	    return -1;
	}

	PRINTF("Public Key: %s\n", private_key);

    PRINTF("Before public key parse:\n");
	if( ( ret = mbedtls_pk_parse_key(&pk, private_key,strlen(private_key)+1,NULL,NULL)) != 0 )
	//if( ( ret = mbedtls_pk_parse_keyfile(&pk, private_key, NULL)) != 0 )		//Enabled via MBEDTLS_FS_IO in ksdk_mbedtls_config.h. Turning this on causes issues in x509_crt.c. Issues because of file navigation impossibilities on K64F?
	{
		PRINTF( " failed\n  ! mbedtls_pk_parse_public_keyfile returned -0x%04x\n", -ret );
		return -1;
	}
	PRINTF("After public key parse:\n");

	unsigned char buf[MBEDTLS_MPI_MAX_SIZE];
	unsigned char buf_base64[2000];				//Max size
	size_t olen = 0;

	/* Calculate the RSA encryption of the data. */
	PRINTF( "\n  . Generating the encrypted value" );
	//fflush( stdout );

	if( ( ret = mbedtls_pk_encrypt( &pk, message, message_length,
									buf, &olen, sizeof(buf),
									mbedtls_ctr_drbg_random, &ctr_drbg ) ) != 0 )
	{
		PRINTF( " failed\n  ! mbedtls_pk_encrypt returned -0x%04x\n", -ret );
		return -1;
	}

	PRINTF( "\n\nEncrypted Message:\n%s\n",buf);

	if( ( ret = mbedtls_base64_encode( buf_base64, 0,&olen,buf,strlen(buf)) ) != 0 )
	{
		PRINTF( " \nfailed  ! mbedtls_base64_encode returned -0x%04x\n", -ret );
		return -1;
	}


	PRINTF( "\nBase64 Message:\n%s\n",buf);

	//TO DO: CONVERT TO BASE64


	return 0;
}

#endif /* MBEDTLS_TIMING_C */
