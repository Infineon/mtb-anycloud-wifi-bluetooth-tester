/*
 * Copyright 2024, Cypress Semiconductor Corporation (an Infineon company) or
 * an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
 *
 * This software, including source code, documentation and related
 * materials ("Software") is owned by Cypress Semiconductor Corporation
 * or one of its affiliates ("Cypress") and is protected by and subject to
 * worldwide patent protection (United States and foreign),
 * United States copyright laws and international treaty provisions.
 * Therefore, you may use this Software only as provided in the license
 * agreement accompanying the software package from which you
 * obtained this Software ("EULA").
 * If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
 * non-transferable license to copy, modify, and compile the Software
 * source code solely for use in connection with Cypress's
 * integrated circuit products.  Any reproduction, modification, translation,
 * compilation, or representation of this Software except as specified
 * above is prohibited without the express written permission of Cypress.
 *
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
 * reserves the right to make changes to the Software without notice. Cypress
 * does not assume any liability arising out of the application or use of the
 * Software or any product or circuit described in the Software. Cypress does
 * not authorize its products for use in any products where a malfunction or
 * failure of the Cypress product may reasonably be expected to result in
 * significant property damage, injury or death ("High Risk Product"). By
 * including Cypress's product in a High Risk Product, the manufacturer
 * of such system or application assumes all risk of such use and in doing
 * so agrees to indemnify Cypress against all liability.
 */
 /** @file
 *
 * This application shows a basic test of how to add a command
  *
 */

#include "cyhal.h"
#include "cybsp.h"
#include <cy_retarget_io.h>
#include <cybsp_wifi.h>
#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include <lwip/tcpip.h>
#include <lwip/api.h>
#include "command_console.h"
#include "iperf_utility.h"
#include "wifi_utility.h"
#include "cy_wcm.h"

#if (defined COMPONENT_WICED_BLE)
#include "bt_utility.h"
#include "bt_cfg.h"
#endif

/*
 * CPU CLOCK FREQUENCY
 */
#define CPU_CLOCK_FREQUENCY 144000000

/* Peripheral clock dividier */
#define CPU_PERI_CLOCK_DIV (2)

#define CHECK_APP_RETURN(expr)  { \
        cy_rslt_t rslt = (expr); \
        if (rslt != CY_RSLT_SUCCESS) \
        { \
           return rslt; \
        } \
}

cy_rslt_t set_cpu_clock ( uint32_t freq );

/* This enables RTOS aware debugging */
volatile int uxTopUsedPriority;

/* wcm parameters */
static cy_wcm_config_t wcm_config;
static cy_wcm_connect_params_t conn_params;

cy_rslt_t ConnectWifi();

#define CONSOLE_COMMAND_MAX_PARAMS     (32)
#define CONSOLE_COMMAND_MAX_LENGTH     (85)
#define CONSOLE_COMMAND_HISTORY_LENGTH (10)

const char* console_delimiter_string = " ";

static char command_buffer[CONSOLE_COMMAND_MAX_LENGTH];
static char command_history_buffer[CONSOLE_COMMAND_MAX_LENGTH * CONSOLE_COMMAND_HISTORY_LENGTH];

#define WIFI_SSID                        ""
#define WIFI_KEY                         ""
#define WIFI_BAND                        CY_WCM_WIFI_BAND_ANY
#define CMD_CONSOLE_MAX_WIFI_RETRY_COUNT 15
#define IP_STR_LEN                       16

#define CY_RSLT_ERROR                    ( -1 )

cy_rslt_t command_console_add_command();

static void get_ip_string(char* buffer, uint32_t ip)
{
    sprintf(buffer, "%lu.%lu.%lu.%lu",
            (unsigned long)(ip      ) & 0xFF,
            (unsigned long)(ip >>  8) & 0xFF,
            (unsigned long)(ip >> 16) & 0xFF,
            (unsigned long)(ip >> 24) & 0xFF);
}

cy_rslt_t ConnectWifi()
{
    cy_rslt_t res ;

    const char *ssid = WIFI_SSID ;
    const char *key = WIFI_KEY ;
    cy_wcm_wifi_band_t band = WIFI_BAND;
    int retry_count = 0;
    cy_wcm_ip_address_t ip_addr;
    char ipstr[IP_STR_LEN];

    memset(&conn_params, 0, sizeof(cy_wcm_connect_params_t));

    while (1)
    {
        /*
        * Join to WIFI AP
        */
        memcpy(&conn_params.ap_credentials.SSID, ssid, strlen(ssid) + 1);
        memcpy(&conn_params.ap_credentials.password, key, strlen(key) + 1);
        conn_params.ap_credentials.security = CY_WCM_SECURITY_WPA2_AES_PSK;
        conn_params.band = band;

        res = cy_wcm_connect_ap(&conn_params, &ip_addr);
        vTaskDelay(500);

        if(res != CY_RSLT_SUCCESS)
        {
            retry_count++;
            if (retry_count >= CMD_CONSOLE_MAX_WIFI_RETRY_COUNT)
            {
                printf("Exceeded max WiFi connection attempts\n");
                return CY_RSLT_ERROR;
            }
            printf("Connection to WiFi network failed. Retrying...\n");
            continue;
        }
        else
        {
            printf("Successfully joined wifi network '%s , result = %ld'\n", ssid, (long)res);
            get_ip_string(ipstr, ip_addr.ip.v4);
            printf("IP Address %s assigned\n", ipstr);
            break;
        }
    }

    return CY_RSLT_SUCCESS;
}

cy_rslt_t command_console_add_command(void) {

    cy_command_console_cfg_t console_cfg;
    cy_rslt_t result = CY_RSLT_SUCCESS;

    printf( "executing command_console_add_remove_command \n");
    console_cfg.serial             = (void *)&cy_retarget_io_uart_obj;
    console_cfg.line_len           = sizeof(command_buffer);
    console_cfg.buffer             = command_buffer;
    console_cfg.history_len        = CONSOLE_COMMAND_HISTORY_LENGTH;
    console_cfg.history_buffer_ptr = command_history_buffer;
    console_cfg.delimiter_string   = console_delimiter_string;
    console_cfg.params_num         = CONSOLE_COMMAND_MAX_PARAMS;
    console_cfg.thread_priority    = CY_RTOS_PRIORITY_NORMAL;
    console_cfg.delimiter_string   = " ";

    /* Initialize command console library */
    result = cy_command_console_init(&console_cfg);
    if ( result != CY_RSLT_SUCCESS )
    {
        printf ("Error in initializing command console library : %ld \n", (long)result);
        goto error;
    }

    /* Initialize Wi-Fi utility and add Wi-Fi commands */
    result = wifi_utility_init();
    if ( result != CY_RSLT_SUCCESS )
    {
        printf ("Error in initializing command console library : %ld \n", (long)result);
        goto error;
    }

    /* Initialize IPERF utility and add IPERF commands */
    iperf_utility_init(&wcm_config.interface);

#if (defined COMPONENT_WICED_BLE)
    /* Initialize Bluetooth utility and add BT commands */
    bt_utility_init();
#endif

    return CY_RSLT_SUCCESS;

error:
    return CY_RSLT_ERROR;

}

static void console_task(void *arg)
{
    cy_rslt_t res;
    
#if !defined COMPONENT_4390X
    printf(" CY_SRAM_SIZE:%ld\n", (long)CY_SRAM_SIZE);
    printf(" Heap size:%d\n", configTOTAL_HEAP_SIZE);
    printf(" SystemCoreClock:%ld\n", (long)SystemCoreClock);
    printf("==============================================\n");
#endif

    /* Initialize wcm */
    wcm_config.interface = CY_WCM_INTERFACE_TYPE_AP_STA;
    res = cy_wcm_init(&wcm_config);
    if(res != CY_RSLT_SUCCESS)
    {
        printf("cy_wcm_init failed with error: %ld\n", (long)res);
        return;
    }
    printf("WCM Initialized\n");

    /* Connect to an AP for which credentials are specified */
    ConnectWifi();

    command_console_add_command();

    while(1)
    {
        vTaskDelay(500);
    }
}


int main(void)
{
    cy_rslt_t result ;

    /* This enables RTOS aware debugging in OpenOCD */
    uxTopUsedPriority = configMAX_PRIORITIES - 1 ;

    /* Initialize the board support package */
    result = cybsp_init() ;
    if( result != CY_RSLT_SUCCESS)
    {
        printf("cybsp_init failed %ld\n", (long)result);
        return CY_RSLT_ERROR;
    }
    CY_ASSERT(result == CY_RSLT_SUCCESS) ;
    /* Enable global interrupts */
    __enable_irq();
    
    /* set CPU clock to CPU_CLOCK_FREQUENCY */
    result = set_cpu_clock(CPU_CLOCK_FREQUENCY);
    CY_ASSERT(result == CY_RSLT_SUCCESS) ;

    cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, CY_RETARGET_IO_BAUDRATE);

    printf("Command console application - AnyCloud !!!\r\n\n");

    xTaskCreate(console_task, "console", 1024*10, "console", 1, NULL) ;
    /* Start the FreeRTOS scheduler */
    vTaskStartScheduler() ;

    return 0;
}

cy_rslt_t set_cpu_clock ( uint32_t freq )
{
    cy_rslt_t ret = CY_RSLT_SUCCESS;
#if !defined COMPONENT_4390X
    uint32_t old_freq;
    cyhal_clock_t clock_pll, clock_hf0 , clock_peri;

#if (CYHAL_API_VERSION >= 2)
    /* Support for HAL latest-v2.x */
    /* Take ownership of HF0 resource */
    CHECK_APP_RETURN(cyhal_clock_reserve(&clock_hf0, &CYHAL_CLOCK_HF[0]));
#else
    /* Support for HAL latest-v1.x */
    /* Get the HF0 resource */
    CHECK_APP_RETURN(cyhal_clock_get(&clock_hf0 , &CYHAL_CLOCK_HF[0] ));
#endif

    old_freq = cyhal_clock_get_frequency(&clock_hf0);
    if ( freq != old_freq )
    {
#if (CYHAL_API_VERSION >= 2)
        /* Take ownership of PLL and PERI resource */
#ifdef COMPONENT_CAT1C
        CHECK_APP_RETURN(cyhal_clock_reserve(&clock_pll , &CYHAL_CLOCK_PLL200[0]));
        CHECK_APP_RETURN(cyhal_clock_reserve(&clock_peri, &CYHAL_CLOCK_PERI[0]));
#else
        CHECK_APP_RETURN(cyhal_clock_reserve(&clock_pll , &CYHAL_CLOCK_PLL[0]));
        CHECK_APP_RETURN(cyhal_clock_reserve(&clock_peri, &CYHAL_CLOCK_PERI));
#endif
#else
        /* Get the PLL and PERI resource */
        CHECK_APP_RETURN(cyhal_clock_get(&clock_pll,  &CYHAL_CLOCK_PLL[0]));
        CHECK_APP_RETURN(cyhal_clock_get(&clock_peri, &CYHAL_CLOCK_PERI));

        /* Initialize, take ownership of, the PLL instance */
        CHECK_APP_RETURN(cyhal_clock_init(&clock_pll));
#endif
        /* Set CPU clock to freq */
        CHECK_APP_RETURN(cyhal_clock_set_frequency(&clock_pll, freq, NULL));

        /* If the PLL is not already enabled, enable it */
        if (!cyhal_clock_is_enabled(&clock_pll))
        {
            CHECK_APP_RETURN(cyhal_clock_set_enabled(&clock_pll, true, true));
        }

#if (CYHAL_API_VERSION < 2)
        /* Support only for mtb-hal-cat1 latest-v1.x */
        /* Initialize, take ownership of, the PERI instance */
        CHECK_APP_RETURN(cyhal_clock_init(&clock_peri));

        /* Initialize, take ownership of, the HF0 instance */
        CHECK_APP_RETURN(cyhal_clock_init(&clock_hf0));
#endif
        /* Set peri clock divider */
        CHECK_APP_RETURN(cyhal_clock_set_divider(&clock_peri, CPU_PERI_CLOCK_DIV));

        /* set HF0 Clock source to PLL */
        CHECK_APP_RETURN(cyhal_clock_set_source(&clock_hf0, &clock_pll));

        cyhal_clock_free(&clock_pll);
        cyhal_clock_free(&clock_peri);
    }
    cyhal_clock_free(&clock_hf0);
#else
    cyhal_clock_t clk_cpu;
    cyhal_clock_get(&clk_cpu, &CYHAL_CLOCK_RSC_CPU);
    cyhal_clock_set_frequency(&clk_cpu, 320000000, 0);
#endif
    return ret;
}

