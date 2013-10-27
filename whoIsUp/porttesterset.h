#ifndef PORTTESTERSET_H
#define PORTTESTERSET_H


#include <QList>
#include "porttester.h"

class PortTesterSet : public PortTester
{
    Q_OBJECT
public:
    PortTesterSet(Host* host, QObject *parent = 0);

    void addPortTester(PortTester *p);
    void update();
protected:
    QList<PortTester*> portTesterList;
};

#endif // PORTTESTERSET_H
