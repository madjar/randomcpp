#include "porttester.h"

PortTester::PortTester(Host* host, QObject *parent) : QObject(parent), host(host), _available(false)
{
}

PortTester::~PortTester()
{
}
