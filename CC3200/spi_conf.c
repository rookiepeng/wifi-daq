/*
 *   spi_conf.c: SPI configuration
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

#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_common_reg.h"
#include "hw_mcspi.h"

#include "rom.h"
#include "rom_map.h"

#include "prcm.h"
#include "spi.h"

#include "spi_conf.h"

unsigned long ulDummy;

void SPI_Init()
{
    // Reset SPI
    MAP_SPIReset(SPI_Interface);

    // Configure SPI interface
    MAP_SPIConfigSetExpClk(SPI_Interface, MAP_PRCMPeripheralClockGet(PRCM_GSPI),
                           SPI_IF_BIT_RATE, SPI_MODE_MASTER, SPI_SUB_MODE_0,
                           (SPI_HW_CTRL_CS |
                            SPI_4PIN_MODE |
                            SPI_TURBO_OFF |
                            SPI_CS_ACTIVELOW |
                            SPI_WL_32));

    // Enable SPI for communication
    MAP_SPIEnable(SPI_Interface);
}

void Master_Send(unsigned long txData)
{
    // Push the character over SPI
    MAP_SPIDataPut(SPI_Interface, txData);

    // Clean up the receive register into a dummy variable
    MAP_SPIDataGet(SPI_Interface, &ulDummy);
}
