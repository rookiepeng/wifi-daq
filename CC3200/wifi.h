/*
 *   wifi.h: header file of wifi.c
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

#ifndef __WIFI_H__
#define __WIFI_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C" {
#endif

#define SSID "WIFI-DAQ"

//*****************************************************************************
//
// Define Packet Size, Rx and Tx Buffer
//
//*****************************************************************************
#define PACKET_SIZE 1024
#define PLAY_WATERMARK 30 * 1024
#define RECORD_BUFFER_SIZE 10 * PACKET_SIZE
#define PLAY_BUFFER_SIZE 70 * PACKET_SIZE

//
// Values for below macros shall be modified for setting the 'Ping' properties
//
//#define PING_INTERVAL 1000 /* In msecs */
//#define PING_TIMEOUT 3000  /* In msecs */
//#define PING_PKT_SIZE 20   /* In bytes */
//#define NO_OF_ATTEMPTS 3
//#define PING_FLAG 0

//*****************************************************************************
//
// UDP Socket Structure
//
//*****************************************************************************
typedef struct UDPSocket
{
    int iSockDesc;             //Socket FD
    struct sockaddr_in Server; //Address to Bind - INADDR_ANY for Local IP
    struct sockaddr_in Client; //Client Address or Multicast Group
    int iServerLength;
    int iClientLength;
} tUDPSocket;

//*****************************************************************************
//void SimpleLinkPingReport(SlPingReport_t *pPingReport);

static long ConfigureSimpleLinkToDefaultState();

static int ConfigureMode(int iMode);

void WlanAPMode(void *pvParameters);

static void InitializeAppVariables();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //__WIFI_H__
