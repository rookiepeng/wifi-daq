/*
 *   app_conf.h: header file of app_conf.c
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

#ifndef APP_CONF_H_
#define APP_CONF_H_

#if defined(gcc)
extern void (*const g_pfnVectors[])(void);
#endif
#if defined(ewarm)
extern uVectorEntry __vector_table;
#endif

#define APP_NAME "WiFI-DAQ"
#define APPLICATION_VERSION "1.0"
#define OSI_STACK_SIZE 2048

#define NOTERM

// Application specific status/error codes
typedef enum {
    // Choosing -0x7D0 to avoid overlap w/ host-driver's error codes
    SOCKET_CREATE_ERROR = -0x7D0,
    BIND_ERROR = SOCKET_CREATE_ERROR - 1,
    LISTEN_ERROR = BIND_ERROR - 1,
    SOCKET_OPT_ERROR = LISTEN_ERROR - 1,
    CONNECT_ERROR = SOCKET_OPT_ERROR - 1,
    ACCEPT_ERROR = CONNECT_ERROR - 1,
    SEND_ERROR = ACCEPT_ERROR - 1,
    RECV_ERROR = SEND_ERROR - 1,
    SOCKET_CLOSE = RECV_ERROR - 1,
    LAN_CONNECTION_FAILED = SOCKET_CLOSE - 1,
    CLIENT_CONNECTION_FAILED = LAN_CONNECTION_FAILED - 1,
    DEVICE_NOT_IN_STATION_MODE = SOCKET_CLOSE - 1,
    STATUS_CODE_MAX = -0xBB8
} e_AppStatusCodes;

void BoardInit(void);
void BoardReboot();

#endif /* APP_CONF_H_ */
