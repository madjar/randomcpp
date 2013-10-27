#ifndef QOOKWINDOW_H
#define QOOKWINDOW_H

#include <QMainWindow>

namespace Ui {
    class QookWindow;
}

class QookWindow : public QMainWindow {
    Q_OBJECT
public:
    QookWindow(QWidget *parent = 0);
    ~QookWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::QookWindow *ui;

private slots:
    void on_action_Add_Recipe_triggered();
    void on_action_Change_Database_triggered();
};

#endif // QOOKWINDOW_H
