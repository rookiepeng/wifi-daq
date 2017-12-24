/****************************************************************************************
//    mydup.h
//
//    Copyright (C) 2017  Zach (Zhengyu) Peng, https://zpeng.me
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************************/

#ifndef MYUDP_H
#define MYUDP_H

#include <QUdpSocket>
#include <QPointF>
#include <QFile>

class MyUDP : public QUdpSocket
{
  Q_OBJECT

public:
  explicit MyUDP(QObject *parent = nullptr);
  bool bindPort(QHostAddress addr, qint16 port);
  void unbindPort();

signals:
  void newMessage(const QString &from, const QString &message);
  void newMessage(const QString &from, const QVector<float> &data);
  void newData(const QVector<QPointF> &plotData);

public slots:
  void readyRead();
  void sendMessage(QHostAddress sender, quint16 senderPort, QString string);

private:
  QUdpSocket *socket;
  QByteArray array;
  //QVector<quint32> timeStampMCU;
  QVector<float> adcData;
  QVector<float> timeStamp; // millisecond

  QVector<QPointF> plotData;
  bool acceptingADCData = false;
};

#endif // MYUDP_H
