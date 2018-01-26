/*
 *   main.c: main function
 * 
 *   Copyright (C) 2017  Zhengyu Peng, https://zpeng.me
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <string.h>

// driverlib includes
#include "hw_types.h"
#include "hw_ints.h"
#include "rom.h"
#include "rom_map.h"
#include "interrupt.h"
#include "prcm.h"
#include "utils.h"
#include "gpio.h"
#include "hw_memmap.h"
#include "spi.h"
#include "adc.h"
#include "hw_adc.h"
#include "hw_udma.h"
#include "udma.h"
#include "udma_if.h"

// ti-rtos includes
#include "osi.h"

// Simplelink includes
#include "simplelink.h"

// common interface includes
#include "common.h"
#ifndef NOTERM
#include "uart_if.h"
#endif
#include "pinmux.h"
#include "gpio_if.h"

#include "gpio_conf.h"
#include "app_conf.h"
#include "wifi.h"
#include "simplelink_conf.h"
#include "tcpudp.h"
#include "spi_conf.h"
#include "adc_conf.h"

unsigned char g_ulStatus = 0;
unsigned long g_ulStaIp = 0;
unsigned long g_ulPingPacketsRecv = 0;
unsigned long g_uiGatewayIP = 0;

//*****************************************************************************
//                            MAIN FUNCTION
//*****************************************************************************
void main()
{
    OsiTaskHandle g_WifiTask = NULL;
    long lRetVal = -1;

    BoardInit();    // Board Initialization
    PinMuxConfig(); // Configure the pinmux settings

    GPIO_PinConfigure(); // Configure IO pins

    SPI_Init(); // SPI Initialization
    //InitAdcDma();

#ifndef NOTERM
    InitTerm(); // Configuring UART
#endif

    // Start the SimpleLink Host
    lRetVal = VStartSimpleLinkSpawnTask(SPAWN_TASK_PRIORITY);
    if (lRetVal < 0)
    {
#ifndef NOTERM
        ERR_PRINT(lRetVal);
#endif
        LOOP_FOREVER();
    }

    // Start the WlanAPMode task
    lRetVal = osi_TaskCreate(WlanAPMode,
                             (const signed char *)"wireless LAN in AP mode",
                             OSI_STACK_SIZE, NULL, 1, &g_WifiTask);
    if (lRetVal < 0)
    {
#ifndef NOTERM
        ERR_PRINT(lRetVal);
#endif
        LOOP_FOREVER();
    }

    osi_start(); // Start the task scheduler
}
