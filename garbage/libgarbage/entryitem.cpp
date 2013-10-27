#include "entryitem.h"

#include <QFont>
#include <QBrush>

QTimer *EntryItem::_timer = 0;

EntryItem::EntryItem(const QPixmap &photo, const QString &login, const QString &passwd, QObject *parent) :
    QObject(parent), login(login), passwd(passwd), ticks(0)
{
    setPhoto(photo);

    connect(timer(), SIGNAL(timeout()),
            SLOT(updateText()));

    textItem.setTextWidth(480);
    textItem.setParentItem(this);
    textItem.setFont(QFont("mono", 42, QFont::Bold));
    textItem.setDefaultTextColor(Qt::green);
    textItem.setZValue(2);

    blackRect.setBrush(Qt::black);
    blackRect.setParentItem(this);
    blackRect.setZValue(1);
}

void EntryItem::startText()
{
    updateText();
}

void EntryItem::updateText()
{
    QString maskedPasswd = passwd;
    for (int i = ticks/10 ; i < passwd.size() ; i++)
        maskedPasswd[i] = QChar(33 + qrand()%94);
    maskedPasswd.insert(ticks/10, QLatin1String("<font color=red>"));
    maskedPasswd.append(QLatin1String("</font>"));
    ticks++;
    if (ticks > passwd.size()*10)
        disconnect(timer(), 0, this, 0);

    textItem.setHtml(QString("<div align=\"center\">%1<br/>%2</div>").arg(login).arg(maskedPasswd));
    textItem.setY( (640 - textItem.boundingRect().height()) / 2 );
    blackRect.setRect(textItem.boundingRect());
    blackRect.setPos(textItem.pos());
}

