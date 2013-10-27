#ifndef ONEPORTTESTER_H
#define ONEPORTTESTER_H

#include <QTcpSocket>


#include "porttester.h"

class OnePortTester : public PortTester
{
    Q_OBJECT
public:
    OnePortTester(Host* host,quint16 number,QObject* parent = NULL);
    void update();

private slots:
    void socketConnected();
    void socketError(QAbstractSocket::SocketError);

private:
    quint16 number;
    QTcpSocket socket;
};

#endif // ONEPORTTESTER_H
