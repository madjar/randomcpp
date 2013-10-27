#include "orporttester.h"

OrPortTester::OrPortTester(Host* host, QObject *parent):PortTesterSet(host,parent)
{
}

bool OrPortTester::available() const
{
    foreach(PortTester *pt, portTesterList)
    {
        if (pt->available())
            return true;
    }
    return false;
}
