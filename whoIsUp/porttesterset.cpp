#include "porttesterset.h"

PortTesterSet::PortTesterSet(Host* host,QObject *parent):PortTester(host,parent)
{
}

void PortTesterSet::addPortTester(PortTester *p)
{
    portTesterList.append(p);
    p->setParent(this);
    connect(p, SIGNAL(updated()),
            this, SIGNAL(updated()));
}

void PortTesterSet::update()
{
    foreach(PortTester *pt, portTesterList)
    {
        pt->update();
    }
}
