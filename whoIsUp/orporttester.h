#ifndef ORPORTTESTER_H
#define ORPORTTESTER_H

#include "porttesterset.h"

class OrPortTester : public PortTesterSet
{
    Q_OBJECT
public:
    OrPortTester(Host* host, QObject *parent = 0);

    bool available() const;
};

#endif // ORPORTTESTER_H
