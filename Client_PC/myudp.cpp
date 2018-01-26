/*
 *   myudp.cpp: UDP socket
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

#include "myudp.h"

MyUDP::MyUDP(QObject *parent) : QUdpSocket(parent)
{
    socket = new QUdpSocket();

    for (quint16 i = 0; i < 1024; i++)
    {
        timeStamp.append(i / 62.5);
    }
}

bool MyUDP::bindPort(QHostAddress addr, qint16 port)
{
    socket->abort();
    bool isBinded = socket->bind(addr, port);
    if (isBinded)
    {
        connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    }
    return isBinded;
}

void MyUDP::sendMessage(QHostAddress sender, quint16 senderPort, QString string)
{
    QByteArray Data;
    Data.append(string);

    // Sends the datagram datagram
    // to the host address and at port.
    socket->writeDatagram(Data, sender, senderPort);
}

void MyUDP::readyRead()
{
    // when data comes in
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    // Receives a datagram no larger than maxSize bytes and stores it in data.
    // The sender's host address and port is stored in *address and *port
    // (unless the pointers are 0).
    socket->readDatagram(buffer.data(), buffer.size(),
                         &sender, &senderPort);

    //qDebug()<<buffer.size();

    for (quint16 i = 0; i < buffer.size(); i += 2)
    {
        adcData.append(((((((quint16)(buffer.at(i))) << 8) + ((quint16)(buffer.at(i + 1)))) >> 2) & 0x0FFF) / pow(2, 12) * 1.48);
    }

    for (quint16 i = 0; i < ((quint16)(adcData.size() / 1024)); i++)
    {
        //emit newMessage(sender.toString(), adcData.mid(0,1024));
        // prepare data for plotting
        for (quint16 i = 0; i < 1024; i++)
        {
            plotData.append(QPointF(timeStamp.at(i), adcData.at(i)));
        }
        emit newData(plotData);
        plotData.clear();
        adcData = adcData.mid(1024, adcData.size() - 1024);
    }
}

void MyUDP::unbindPort()
{
    disconnect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    socket->close();
}
