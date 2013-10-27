#ifndef ENTRY_H
#define ENTRY_H

#include <QObject>
#include <QString>
#include <QPixmap>
#include <QNetworkReply>

class Entry : public QObject
{
    Q_OBJECT
public:
    explicit Entry(int id, QObject *parent = 0);

    QString getLogin () const;
    QString getPasswd () const;
    QPixmap getPixmap () const {return pixmap;}
    bool isValid () const {return valid;}

signals:
    void ready();

private slots:
    void pageDownloadFinished();
    void photoDownloadFinished();

private:
    QString firstName;
    QString lastName;
    QString birth;
    QString email;
    QPixmap pixmap;
    bool valid;

    QNetworkReply *reply;

    QString unescape(const QString &s) const;
    QString remove_accents(const QString &s) const;
};

#endif // ENTRY_H
