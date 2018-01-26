/*
 *   tcpudp.h: header file of tcpudp.c
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

#ifndef __TCPUDP_H__
#define __TCPUDP_H__

#define IP_ADDR 0xc0a80102 /* 192.168.1.2 */
#define PORT_NUM 1234
#define BUF_SIZE 1400

int BsdUdpClient();
//int BsdUdpServer(unsigned short usPort);

//int BsdTcpClient(unsigned short usPort);
void UpdateUDPClientIP(unsigned long ip_addr, unsigned short port);
void BsdTcpServer(unsigned short usPort);

int UDP_send(char *g_ulBuffer, short sBufLen);
int TCP_send(char *g_ulBuffer, short sBufLen);

void CommandProcess();

#endif //  __TCPUDP_H__
