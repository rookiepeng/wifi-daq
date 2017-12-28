/****************************************************************************************
//    Copyright (C) 2017  Zhengyu Peng, zhengyu.peng@ttu.edu
*****************************************************************************************/

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
