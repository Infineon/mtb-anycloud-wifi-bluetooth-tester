/*
 * Copyright 2020 Cypress Semiconductor Corporation
 * SPDX-License-Identifier: Apache-2.0
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 /** @file
 *
 * This application shows a basic test of how to add a command
  *
 */
//#define ENABLE_BT_COMMAND_TEST 1
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
#include "cy_lwip.h"

#ifdef ENABLE_BT_COMMAND_TEST
#include "bt_utility.h"
#include "bt_cfg.h"
#endif

/* This enables RTOS aware debugging */
volatile int uxTopUsedPriority;

/* The primary WIFI driver  */
static whd_interface_t iface ;

/* This enables RTOS aware debugging */
volatile int uxTopUsedPriority ;

cy_rslt_t ConnectWifi();

#define CONSOLE_COMMAND_MAX_PARAMS     (32)
#define CONSOLE_COMMAND_MAX_LENGTH     (85)
#define CONSOLE_COMMAND_HISTORY_LENGTH (10)

const char* console_delimiter_string = " ";

static char command_buffer[CONSOLE_COMMAND_MAX_LENGTH];
static char command_history_buffer[CONSOLE_COMMAND_MAX_LENGTH * CONSOLE_COMMAND_HISTORY_LENGTH];

#define WIFI_SSID   ""
#define WIFI_KEY    ""
#define MAX_WIFI_RETRY_COUNT 15

#define CY_RSLT_ERROR ( -1 )

cy_rslt_t command_console_add_command();

static void donothing(void *arg)
{
}

cy_rslt_t ConnectWifi()
{
    cy_rslt_t res ;

    const char *ssid = WIFI_SSID ;
    const char *key = WIFI_KEY ;
    int retry_count = 0;
    cy_lwip_nw_interface_t nw_interface;

    whd_ssid_t ssiddata ;
    tcpip_init(donothing, NULL) ;
    printf("LWiP TCP/IP stack initialized\n") ;
    /*
     *   Initialize wifi driver
     */
    cybsp_wifi_init_primary(&iface) ;
    printf("WIFI driver initialized \n") ;

    while (1)
    {
         /*
         * Join to WIFI AP
         */
         ssiddata.length = strlen(ssid) ;
         memcpy(ssiddata.value, ssid, ssiddata.length) ;
         res = whd_wifi_join(iface, &ssiddata, WHD_SECURITY_WPA2_AES_PSK, (const uint8_t *)key, strlen(key)) ;
         vTaskDelay(500);

         if (res != CY_RSLT_SUCCESS)
         {
              retry_count++;
              if (retry_count >= MAX_WIFI_RETRY_COUNT)
              {
                  printf("Exceeded max WiFi connection attempts\n");
                  return CY_RSLT_ERROR;
              }
              printf("Connection to WiFi network failed. Retrying...\n");
              continue;
         }
         else
         {
              printf("Successfully joined wifi network '%s , result = %ld'\n", ssid, res) ;
              break;
         }
    }

    nw_interface.role = CY_LWIP_STA_NW_INTERFACE;
    nw_interface.whd_iface = iface;

    cy_lwip_add_interface(&nw_interface, NULL);

    cy_lwip_network_up(&nw_interface);

    struct netif *net = cy_lwip_get_interface(CY_LWIP_STA_NW_INTERFACE);

    while (true)
    {
        if (net->ip_addr.u_addr.ip4.addr != 0)
        {
             printf("IP Address %s assigned\n", ip4addr_ntoa(&net->ip_addr.u_addr.ip4)) ;
             break ;
        }
        vTaskDelay(100) ;
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
    console_cfg.delimiter_string   = " ";

    /* Initialize command console library */
    result = cy_command_console_init(&console_cfg);
    if ( result != CY_RSLT_SUCCESS )
    {
        printf ("Error in initializing command console library : %ld \n", result);
        goto error;
    }

    /* Initialize IPERF utility and add IPERF commands */
    iperf_utility_init(&iface);

    /* Initialize Bluetooth utility and add BT commands */
#ifdef ENABLE_BT_COMMAND_TEST
    bt_utility_init();
#endif

    return CY_RSLT_SUCCESS;

error:
    return CY_RSLT_ERROR;

}

static void console_task(void *arg)
{
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
        printf("cybsp_init failed %ld\n", result);
        return -1;
    }
    CY_ASSERT(result == CY_RSLT_SUCCESS) ;
    /* Enable global interrupts */
    __enable_irq();

    cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, CY_RETARGET_IO_BAUDRATE);

    printf("Command console application - AnyCloud !!!\r\n\n");

    xTaskCreate(console_task, "console", 1024*10, "console", 1, NULL) ;
    /* Start the FreeRTOS scheduler */
    vTaskStartScheduler() ;

    return 0;
}
