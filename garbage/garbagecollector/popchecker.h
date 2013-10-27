#ifndef POPCHECKER_H
#define POPCHECKER_H

#include <QObject>
#include <QString>
#include <QSslSocket>
#include <QQueue>

class PopChecker : public QObject
{
    Q_OBJECT
public:
    PopChecker(const QString &host, quint16 port, const QString &login, const QString &passwd, QObject *parent = 0);
    void check();

signals:
    void checkFinished(bool);

private slots:
    void go();
    void encrypted();
    void disconnected();

private:
    QSslSocket socket;
    QString host;
    quint16 port;
    QString login;
    QString passwd;

    static QQueue<PopChecker*> *waitingQueue;
    static int currentTasks;
};

#endif // POPCHECKER_H
