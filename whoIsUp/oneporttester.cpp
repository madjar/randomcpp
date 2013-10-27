#include "oneporttester.h"

#include <QTcpSocket>
#include <QIODevice>
#include <QtDebug>
#include "host.h"

OnePortTester::OnePortTester(Host* host,quint16 number,QObject* parent)
    :PortTester(host,parent),number(number)
{
    connect(&socket, SIGNAL(connected()),
            this, SLOT(socketConnected()));
    connect(&socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(socketError(QAbstractSocket::SocketError)));

    update();
}

void OnePortTester::update()
{
    if(!host->address().isNull() && socket.state() == QAbstractSocket::UnconnectedState)
    {
        qDebug() << "Update de port : " << host->address() << ":" << number;
        socket.connectToHost(host->address(), number, QIODevice::NotOpen);
    }
}

void OnePortTester::socketConnected()
{
    _available = true;
    socket.disconnectFromHost();
    emit updated();
}
void OnePortTester::socketError(QAbstractSocket::SocketError /*error*/)
{
    _available = false;
    socket.disconnectFromHost();
    emit updated();
}
