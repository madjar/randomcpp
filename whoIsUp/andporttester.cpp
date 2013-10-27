#include "andporttester.h"

AndPortTester::AndPortTester(Host* host, QObject *parent):PortTesterSet(host,parent)
{
}

bool AndPortTester::available() const
{
    foreach(PortTester *pt, portTesterList)
    {
        if (! pt->available())
            return false;
    }
    return true;
}
