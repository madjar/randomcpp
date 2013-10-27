#ifndef PORTTESTER_H
#define PORTTESTER_H

#include <QObject>

class Host;

class PortTester : public QObject
{
    Q_OBJECT
public:
    PortTester(Host* host, QObject *parent = 0);
    virtual ~PortTester();

    virtual bool available() const
    {
        return _available;
    }

    virtual void update() = 0;

signals:
    void updated();

protected:
    Host* host;
    bool _available;
};

#endif // PORTTESTER_H
