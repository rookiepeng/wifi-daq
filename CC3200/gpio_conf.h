/*
 *   gpio_conf.h: header file of gpio_conf.c
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

#ifndef GPIO_CONF_H_
#define GPIO_CONF_H_

/*
// for Launchpad
#define GPIO_LED1 9
#define GPIO_LED2 10
#define GPIO_LED3 11

typedef enum {
  NO_SW,
  SW1 = 0x1, // SW1/Reset Button
  SW2 = 0x2, // SW2/GP22/Pin15
  SW3 = 0x4  // SW3/GP13/Pin4
} eSwNum;
*/

// for decoder control
#define GPIO_A 13
#define GPIO_B 12
#define GPIO_C 11

// for RF switches
#define GPIO_D1 6
#define GPIO_D2 1
#define GPIO_D3 0
#define GPIO_D4 8
#define GPIO_STORE 7

// for baseband switch
#define GPIO_S3 22
#define GPIO_S2 23
#define GPIO_S1 24
#define GPIO_S0 28

// for LEDs
#define LED0 24
#define LED1 28

void GPIO_GetPortNPin(unsigned char ucPin, unsigned int *puiGPIOPort, unsigned char *pucGPIOPin);
void GPIO_Set(unsigned char ucPin, unsigned int uiGPIOPort, unsigned char ucGPIOPin, unsigned char ucGPIOValue);
unsigned char GPIO_Get(unsigned char ucPin, unsigned int uiGPIOPort, unsigned char ucGPIOPin);

void GPIO_PinConfigure();

// GPIO interrupts
static unsigned char GetPeripheralIntNum(unsigned int uiGPIOPort);
void GPIO_IF_Init(void (*SW2IntHandler)(void), void (*SW3IntHandler)(void));
void GPIO_IF_ConfigureNIntEnable(unsigned int uiGPIOPort, unsigned char ucGPIOPin, unsigned int uiIntType, void (*pfnIntHandler)(void));
void GPIO_IF_EnableInterrupt(unsigned char ucSwitch);
void GPIO_IF_DisableInterrupt(unsigned char ucSwitch);

void GPIO_LedOn(char ledNum);
void GPIO_LedOff(char ledNum);
unsigned char GPIO_LedStatus(unsigned char ucGPIONum);
void GPIO_LedToggle(unsigned char ucLedNum);

#endif /* GPIO_CONF_H_ */
