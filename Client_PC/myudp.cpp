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

    /*
    if (acceptingADCData)
    {
        array.append(buffer);
    }
    else
    {
        emit newMessage(sender.toString(), buffer);
    }

    if (array.right(7) == "ADCSTOP")
    {
        acceptingADCData = false;
        array = array.mid(7, array.size() - 14);
        qDebug() << array.size();

        for (qint32 i = 0; i < 1024; i++)
        {
            // Pong
            //timeStampMCU.append(((((quint32)array.at(i+1024 * 16)) << 16) + (((quint32)array.at(i + 1024*17)) << 8) + ((quint32)array.at(i + 1024*18))) >> 6);
            adcData.append(((float)((((((quint16)array.at(i + 1024 * 0)) << 8) + ((quint16)array.at(i + 1024 * 1))) >> 2) & 0x0FFF)) / pow(2, 12) * 1.48);
            //timeStampMCU.append(((((quint32)array.at(i+1024 * 20)) << 16) + (((quint32)array.at(i + 1024*21)) << 8) + ((quint32)array.at(i + 1024*22))) >> 6);
            adcData.append(((float)((((((quint16)array.at(i + 1024 * 2)) << 8) + ((quint16)array.at(i + 1024 * 3))) >> 2) & 0x0FFF)) / pow(2, 12) * 1.48);
            //timeStampMCU.append(((((quint32)array.at(i+1024 * 24)) << 16) + (((quint32)array.at(i + 1024*25)) << 8) + ((quint32)array.at(i + 1024*26))) >> 6);
            adcData.append(((float)((((((quint16)array.at(i + 1024 * 4)) << 8) + ((quint16)array.at(i + 1024 * 5))) >> 2) & 0x0FFF)) / pow(2, 12) * 1.48);
            //timeStampMCU.append(((((quint32)array.at(i+1024 * 28)) << 16) + (((quint32)array.at(i + 1024*29)) << 8) + ((quint32)array.at(i + 1024*30))) >> 6);
            adcData.append(((float)((((((quint16)array.at(i + 1024 * 6)) << 8) + ((quint16)array.at(i + 1024 * 7))) >> 2) & 0x0FFF)) / pow(2, 12) * 1.48);
        }
        //emit newMessage(sender.toString(), adcData);

        // prepare data for plotting
        //for (quint16 i = 0; i < 4096; i++)
        //{
        //    plotData.append(QPointF(timeStamp.at(i), adcData.at(i)));
        //}
        //emit newData(plotData);

        //qDebug() << adcData.size();
        //qDebug() << adcData.mid(0, 1024);
        //qDebug() << timeStamp.mid(0, 1024);
        //qDebug() << adcData.mid(1024,1024);
        //qDebug() << adcData.mid(1024*2,1024);
        //qDebug() << adcData.mid(1024*3,1024);
        //qDebug() << adcData.mid(1024*4,1024);
        //qDebug() << adcData.mid(1024*5,1024);
        //qDebug() << adcData.mid(1024*6,1024);
        //qDebug() << adcData.mid(1024 * 7, 1024);
        //qDebug() << timeStampMCU;

        array.clear();
        adcData.clear();
        plotData.clear();
        //timeStampMCU.clear();
    }*/
}

void MyUDP::unbindPort()
{
    disconnect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    socket->close();
}
