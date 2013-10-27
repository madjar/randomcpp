#ifndef LOCALPICTURESEARCHER_H
#define LOCALPICTURESEARCHER_H

#include <QObject>
#include <QPixmap>
#include <QDir>
#include <QTimer>

class LocalPictureSearcher : public QObject
{
    Q_OBJECT
public:
    explicit LocalPictureSearcher(const QString &dirname, QObject *parent = 0);

public slots:
    void findPhotos();

signals:
    void photoFound(QPixmap);
    void matchFound(QPixmap, QString, QString);

private:
    QDir dir;
};

#endif // LOCALPICTURESEARCHER_H
