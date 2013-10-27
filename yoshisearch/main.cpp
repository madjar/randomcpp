#include <QApplication>
#include <QTreeView>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QLineEdit>

#include "yoshimodel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTreeView view;
    YoshiModel model;

    model.setSearch("south park");

    view.setModel(&model);
    view.setRootIsDecorated(false);
    view.header()->setResizeMode(1,QHeaderView::ResizeToContents);
    view.header()->setResizeMode(0,QHeaderView::ResizeToContents);

    QLineEdit lineEdit;
    QObject::connect(&lineEdit, SIGNAL(textEdited(QString)),
                     &model, SLOT(setSearch(QString)));

    QVBoxLayout layout;
    layout.addWidget(&lineEdit);
    layout.addWidget(&view);

    QWidget window;
    window.setLayout(&layout);
    window.show();

    return app.exec();
}
