#ifndef ANDPORTTESTER_H
#define ANDPORTTESTER_H

#include "porttesterset.h"

class AndPortTester : public PortTesterSet
{
    Q_OBJECT
public:
    AndPortTester(Host* host, QObject *parent = 0);

    bool available() const;
};

#endif // ANDPORTTESTER_H
