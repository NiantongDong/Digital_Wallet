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
#include "mbedtls/md.h"
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

#if defined(MBEDTLS_MEMORY_signFER_ALLOC_C)
#include "mbedtls/memory_signfer_alloc.h"
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
 * Size to use for the alloc signfer if MEMORY_signFER_ALLOC_C is defined.
 */
#define HEAP_SIZE       (1u << 16)  // 64k

#define signSIZE         1024
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
                           (ii * signSIZE / 1024) / (((float)(tsc2 - tsc1)) / CLOCK_GetCoreSysClkFreq()), \
                           (((float)(benchmark_mbedtls_timing_hardclock() - tsc2)) / (jj * signSIZE)));   \
        }                                                                                                \
    } while (0)

#if defined(MBEDTLS_MEMORY_signFER_ALLOC_C) && defined(MBEDTLS_MEMORY_DEBUG)

#define MEMORY_MEASURE_INIT                                             \
    size_t max_used, max_blocks, max_bytes;                             \
    size_t prv_used, prv_blocks;                                        \
    mbedtls_memory_signfer_alloc_cur_get( &prv_used, &prv_blocks );      \
    mbedtls_memory_signfer_alloc_max_reset( );

#define MEMORY_MEASURE_PRINT( title_len )                               \
    mbedtls_memory_signfer_alloc_max_get( &max_used, &max_blocks );      \
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

unsigned char sign[signSIZE];

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
	"MIIBITANBgkqhkiG9w0BAQEFAAOCAQ4AMIIBCQKCAQBZNL64AcOuPy8hcR7nTTvH\n"
	"IVWHElEJz56XM3B34MqdHwcKZ/N6+7+Ya9GZu5xxi3uFhHdvBhSgs+N6hIzVFHa5\n"
	"sUwtkbVR+aSHHCYVD1QxEJHJKm2DlduxffDotIlMjK2KLj3jVok/X481YBC0rTQY\n"
	"vExV4sXXeQZDuYB5Mrca1YmmspwSq1WogPbrZXHavdJYR6btyPH1t4VnpBoRyYiJ\n"
	"kNWYbDbEJDAWcsl0qILPHzGjuZvmgk/UPyckBBvePd1cbtZlvTX0S0+HhvtjoKBR\n"
	"t958cekklpOXGgM5BDHgBnIoExXHKs32uu44UanlcUyteIfsGpkWlcG6KHAVLMGF\n"
	"AgMBAAE=\n"
	"-----END PUBLIC KEY-----\n\0";

//MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAp0Jb2UNeN0FNyFNWbqzoXHEyZ3BSRv0XyHwS1pmQwiIcLCo6goOv6RRutJOUee9A47pv8BDUniCV4rL6gL9nUp/lGBwocqkwcON9lOEQq3U53VDlm+/eY5OsBo0AfoXYugA1wj0snlCfxImtcd2J8MML+4vdScO90fD8Lakkjh+Ak0xhhw70QGRzsSMgkH1XJzEf0GLg3e5SDvRvXrbMco8ELGFB9NhVdjoBwfeAw+lhnudXaaAfhX3lyhg3Ssy0yivFei82p4FT4as8E+NBAQ2p+CDJSTb2GFDD3Aa4djFkPpIHWhNZNrXpl7Zl3v0Pgccwzl5GUQfLMzSGkUNkCQIDAQAB



unsigned char *private_key =
		"-----BEGIN RSA PRIVATE KEY-----\n"
		"MIIEoQIBAAKCAQBZNL64AcOuPy8hcR7nTTvHIVWHElEJz56XM3B34MqdHwcKZ/N6\n"
		"+7+Ya9GZu5xxi3uFhHdvBhSgs+N6hIzVFHa5sUwtkbVR+aSHHCYVD1QxEJHJKm2D\n"
		"lduxffDotIlMjK2KLj3jVok/X481YBC0rTQYvExV4sXXeQZDuYB5Mrca1YmmspwS\n"
		"q1WogPbrZXHavdJYR6btyPH1t4VnpBoRyYiJkNWYbDbEJDAWcsl0qILPHzGjuZvm\n"
		"gk/UPyckBBvePd1cbtZlvTX0S0+HhvtjoKBRt958cekklpOXGgM5BDHgBnIoExXH\n"
		"Ks32uu44UanlcUyteIfsGpkWlcG6KHAVLMGFAgMBAAECggEAGHr6D8MkMTBTvciu\n"
		"Y2l1iyshroSfSqL4caQDLFK7J605IGjwj4KAzNJh3d93ik1t43E72XMAvC1BswCn\n"
		"KV6JSmJWdnbzHID23sEhzku7ng9fAqarER5SAP5/20yYFTLR+QbBox6/YW3W/h3T\n"
		"19FkZ5ldFYC7LGuhBXrlv9zkFO/Lx84RozjQ7Q8k/Fp/Zyqs28LM4HbOzW8AOSSH\n"
		"VEftLjaOF6tvXP03AJ/xZgNOP2rsJ8C7YcaituoD231mOjRqHVLhRsgnCEr+ixQq\n"
		"qvln9+oze6tjdmAVv+zk0KUJnWdwOTEKz77qX0m6TgNWOClWmehxhZa+QdXEp89b\n"
		"adDirQKBgQCh655/xOQqueQyLvOQCuRB+haSg1nO6b+fB2QwJBqula2EeIhLwoas\n"
		"Ww3DVEF/RGaLSEyhxlCu3IxrvvUzRVUTYSVJd3ZWzdEm19qZvHVuCy2icVFSLiAk\n"
		"G4wJ4+snK759F7urpJdKr2bJZ/9RXy7TsJg6L5s+D54VIPNJiMPq1wKBgQCNCXB4\n"
		"H657037VZarALnoYd9Fjn+qDnx+Eq9JrIkneQ30coEY0MSJ5q7lCyvlASFwMiLS3\n"
		"BODfMO/xG2Sooo0IEwtINqMGmdDKNqxtgguRrppbKThQ5+v+NShq3rqx0gBHnNBY\n"
		"6jLrK5lpo6VesehcKQeZDGO+X3Xd2roX/6/nAwKBgBkwQSjZJTFsV45i9Wq79wQ4\n"
		"dlh2bHseq7t+d9xxUWFFUYfhBDrc2Pxo8bwoGERHDLiwF5O2+QgqsQF15EkEiRaJ\n"
		"rzY9ikA4pkenno753T6wKHozrJXfLQrQ6jkDpqoiSPDGx2ANK6fnn1LHhdVPvEYc\n"
		"G6I5k6nU3h+lT5Np3ihjAoGABby+kIRpaqwd2rx6B7tcSCaHpA/bUGNmutTqiGUq\n"
		"sBn6uvFiKbld96kerjLnlM/cvr3I7DEMnMe22w4MODf0mMF9kgB2/UvAjJlQxlul\n"
		"8NUzfkXc/p2QohSzgjVxTs6GKGOerh9I1vw9D2kSzxlZpHYe0wEIBbSIbO/65gMG\n"
		"utUCgYAut1jlLn3zX0DWyNKkqE1w/izhsbNg6ueScLp/G4g6jD7rc4SgE+qtxwbi\n"
		"nvDt5IL/0TIci2+dPnfdP7ZV4iypSVSLXkUMERjhROH5c/U8C4cMaiw+QItW9lf6\n"
		"j8wLPRcGl4FbzmYLGhvJKZ2IJvKBeh54JHSEna0eFAKzphYLcw==\n"
		"-----END RSA PRIVATE KEY-----\n\0";

/* Mbedtls context creation and init */
static mbedtls_ctr_drbg_context ctr_drbg;
static mbedtls_pk_context pk_public;
static mbedtls_pk_context pk_private;
static mbedtls_entropy_context entropy;


static void print_hex(const char *title, const unsigned char buf[], size_t len)
{
    mbedtls_printf("%s: \n", title);

    for (size_t i = 0; i < len; i++)
        mbedtls_printf("%02x", buf[i]);

    mbedtls_printf("\n");
}
int main( int argc, char *argv[] )
{
    int i;
    unsigned char tmp[200];
    char title[TITLE_LEN];
    todo_list todo;
#if defined(MBEDTLS_MEMORY_signFER_ALLOC_C)
    unsigned char alloc_sign[HEAP_SIZE] = { 0 };
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
    char *personalization = "oh lord let this work";
    char *new_message = "Hello World again!\n";

    static const char Test[] = "Hash Hash Hash";
    static const unsigned char *Test_buffer_hash =  (const unsigned char *) Test;

	unsigned char sign[2048]="\0";
	unsigned char sign_base64_encoded[2048]="\0";
	unsigned char sign_base64_decoded[2048]="\0";
	unsigned char signed_base64_encoded[2048]="\0";				/* Explicit encoded & decoded variables to show real life process, instead of just passing through original signfer */
	unsigned char signed_base64_decoded[2048]="\0";
	size_t olen = 0, olen_base64 = 0;

	mbedtls_ctr_drbg_init( &ctr_drbg );
	mbedtls_pk_init( &pk_public );
	mbedtls_pk_init( &pk_private );
	mbedtls_entropy_init( &entropy );

/* Setting Randomness Generator */
	ret = mbedtls_ctr_drbg_seed( &ctr_drbg , mbedtls_entropy_func, &entropy,
	                 (const unsigned char *) personalization,
	                 strlen( personalization ) );
	if( ret != 0 )
	{
	    return -1;
	}
	PRINTF("Message to be signed: %s\n", message);

/* Loading the keys into pk_ */
	if( ( ret = mbedtls_pk_parse_public_key(&pk_public, public_key,strlen(public_key)+1)) != 0 )
	{
		PRINTF( " failed\n  ! mbedtls_pk_parse_public_keyfile (public key) returned -0x%04x\n", -ret );
		return -1;
	}

	if( ( ret = mbedtls_pk_parse_key(&pk_private, private_key,strlen(private_key)+1,NULL,42)) != 0 )		/* But what's the question? */
	{
		PRINTF( " failed\n  ! mbedtls_pk_parse_key (private key) returned -0x%04x\n", -ret );
		return -1;
	}

	PRINTF("Done loading keys!\n");

/* Signing our message, with no hashing. We want anyone with public key to read contents. */
/* Hash function Simple way*/
	PRINTF("Start Hashing: \n");
	unsigned char hash_sign[32]="\0";
	unsigned char hash_message[32]="\0";
//	mbedtls_sha256_ret(sign, strlen(sign), hash_sign, 0);
//	print_hex("SHA256 Value for signature:", hash_sign, sizeof hash_sign);
	mbedtls_sha256_ret(message, strlen(message), hash_message, 0);
	print_hex("SHA256 Value for message:", hash_message, sizeof hash_message);
	fflush( stdout );
	PRINTF("Olen: %d\n",olen);
    if( ( ret = mbedtls_pk_sign( &pk_private, MBEDTLS_MD_SHA256 , hash_message, 0, sign, &olen,
                         mbedtls_ctr_drbg_random, &ctr_drbg ) ) != 0 )
    {
    	PRINTF( " failed\n  ! mbedtls_pk_sign returned -0x%04x\n", (unsigned int) -ret );
        goto exit;
    }
    mbedtls_sha256_ret(sign, strlen(sign), hash_sign, 0);
    print_hex("SHA256 Value for signature:", hash_sign, sizeof hash_sign);


	const char hardcode[]="LGFErzqw+rC6O2zN3RNy79+eVVQ/NdAkq4tPbsvDHEaPPJcnIE1GSAoiEJ7Ppey5727SJRg7CGn4Zr6XBqRd5a6egINn3NGnKzuYnKurgnBKJukmoDXsA05Kevz4egXiLVVEOBg3e0BYWqmILGtk0BvLjv8RomiRktwChwiv25bocoLQ4mGRdXp9KKR0AYddNxSMIJx4Buf7qj6f/EmAc//yQrlT3tN3O9T2wFGgwu4r6R1VaviY7k5YAI2mInWztd38B9X6obkc84jiAMqHpHvTPtaevZ5OlrmWuAIzQYbJPkkOjm4mtBNmHMJ7eh/fR6W2ugrfqZDteNlQgSn+Mg==";
	PRINTF("Hardcode sign: %s/n",hardcode);
    fflush( stdout );
	if( ( ret = mbedtls_base64_decode(signed_base64_decoded,2048,olen,hardcode,sizeof(hardcode)) != 0 ))	//Isn't this size too big for RSA2048?
	{
		PRINTF( " \nfailed\nOlen = %d\nmbedtls_base64_encode returned -0x%04x\n", olen,-ret );
		return -1;
	}
/* Verification using our public key */			//mbedtls_pk_verify_ext
	fflush( stdout );
	if( ( ret = mbedtls_pk_verify( &pk_public,MBEDTLS_MD_SHA256,hash_message,0,signed_base64_decoded,sizeof(signed_base64_decoded)) ) != 0 )	//Isn't this size too big for RSA2048?
	{
		PRINTF( " \nfailed\nOlen = %d\nHash Length: %d\nSig Length: %d\n\nmbedtls_pk_verify returned -0x%04x\n", olen,strlen(message),strlen(signed_base64_decoded),-ret );
		return -1;
	}


exit:
	mbedtls_ctr_drbg_free(&ctr_drbg);
	mbedtls_entropy_free(&entropy);
	mbedtls_pk_free(&pk_public);
	mbedtls_pk_free(&pk_private);
	PRINTF("Goodbye world!\n");
	return 0;
}

#endif /* MBEDTLS_TIMING_C */

	/* Ben's spooky code graveyard, because he's a hoarder */

/*	if( ( ret = mbedtls_pk_encrypt( &pk_public, message, strlen(message),
									sign, &olen, sizeof(sign),
									mbedtls_ctr_drbg_random, &ctr_drbg ) ) != 0 )
	{
		PRINTF( " failed\n  ! mbedtls_pk_encrypt returned -0x%04x\n", -ret );
		return -1;
	}*/
/* Base64 conversion of binary encrypted string */
/*	if( ( ret = mbedtls_base64_encode( encrypt_base64, 2048,&olen_base64,sign,olen) ) != 0 )	//Isn't this size too big for RSA2048?
	{
		PRINTF( " \nfailed\nOlen = %d\nmbedtls_base64_encode returned -0x%04x\n", olen,-ret );
		return -1;
	}

	PRINTF( "\nRet=%d\nolen_base64=%d\nBase64 Message:\n%s\n",ret,olen_base64,encrypt_base64);*/

/* Decrypting Message! */
/*

	unsigned char decrypted_message[2048];

	if( ( ret = mbedtls_pk_decrypt( &pk_private, sign, strlen(sign), decrypted_message, &olen, sizeof(decrypted_message),
	                                mbedtls_ctr_drbg_random, &ctr_drbg ) ) != 0 )
	{
	    printf( "failed   mbedtls_pk_decrypt returned -0x%04x\n", -ret );
	    return -1;
	}

	PRINTF("Decrypted Message: %s\n",decrypted_message);*/


