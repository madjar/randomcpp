#include <QApplication>

#include "localpicturesearcher.h"
#include "../libgarbage/garbage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Garbage g;
    g.show();

    LocalPictureSearcher lps(a.arguments().at(1));
    QObject::connect(&lps, SIGNAL(photoFound(QPixmap)),
                     &g, SLOT(entry(QPixmap)));
    QObject::connect(&lps, SIGNAL(matchFound(QPixmap,QString,QString)),
                     &g, SLOT(match(QPixmap,QString,QString)));

    return a.exec();
}
