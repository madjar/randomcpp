#include "popchecker.h"

#include <QTextStream>
#include <QtDebug>

QQueue<PopChecker*> *PopChecker::waitingQueue = 0;
int PopChecker::currentTasks = 0;

PopChecker::PopChecker(const QString &host, quint16 port, const QString &login, const QString &passwd, QObject *parent)
    : QObject(parent), host(host), port(port), login(login), passwd(passwd)
{
    connect (&socket, SIGNAL(encrypted()),
             SLOT(encrypted()));
    connect (&socket, SIGNAL(disconnected()),
             SLOT(disconnected()));
}

void PopChecker::check()
{
    if (waitingQueue == 0)
        waitingQueue = new QQueue<PopChecker*>;

    if (waitingQueue->size() < 3)
        go();
    else
        waitingQueue->enqueue(this);
}

void PopChecker::go()
{
    currentTasks++;
    socket.connectToHostEncrypted(host, port);
}

void PopChecker::encrypted()
{
    QTextStream stream(&socket);
    stream << "USER " << login << endl;
    stream << "PASS " << passwd << endl;
    stream << "QUIT" << endl;
}

void PopChecker::disconnected()
{
    QTextStream stream(&socket);
    QString output = stream.readAll();

    if(output.contains("-ERR"))
    {
        emit checkFinished(false);
    }
    else if (output.contains("+OK"))
    {
        emit checkFinished(true);
    }
    else
    {
        emit checkFinished(false);
        qDebug() << "invalid return from server :" << output;
    }

    currentTasks--;
    if (!waitingQueue->isEmpty())
        waitingQueue->dequeue()->go();
}
