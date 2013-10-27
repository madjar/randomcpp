#ifndef DBCONNEXIONWIZARD_H
#define DBCONNEXIONWIZARD_H

#include <QWizard>
#include <QLabel>
#include <QRadioButton>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QSpinBox>
#include <QCheckBox>

class DBConnexionWizard : public QWizard
{
    Q_OBJECT
public:
    enum { Page_Intro, Page_DBChoice, Page_SQLite, Page_OtherDB,
                Page_End };

    explicit DBConnexionWizard(QWidget *parent = 0);

    void accept();

    static bool connectToDb();
    static void populateDb();
};

class IntroPage : public QWizardPage
{
    Q_OBJECT

public:
    IntroPage(QWidget *parent = 0);

    int nextId() const;

private:
    QLabel *label;
};

class DBChoicePage : public QWizardPage
{
    Q_OBJECT

public:
    DBChoicePage(QWidget *parent = 0);

    int nextId() const;

private:
    QLabel *label;
    QRadioButton *sqlite;
    QRadioButton *other;

};

class SQLitePage : public QWizardPage
{
    Q_OBJECT

public:
    SQLitePage(QWidget *parent = 0);

    int nextId() const;

private slots:
    void onDefaultDB(bool toggle);
    void onMemory(bool toggle);
    void onCustomLocation(bool toggle);
    void onLocationButton();

private:
    QLabel *label;
    QRadioButton *defaultDB;
    QRadioButton *memory;
    QRadioButton *customLocation;
    QLineEdit *locationEdit;
    QPushButton *locationButton;
};

class OtherDBPage : public QWizardPage
{
    Q_OBJECT

public:
    OtherDBPage(QWidget *parent = 0);

    int nextId() const;

private:
    QLabel *label;
    QComboBox *driver;
    QLineEdit *host;
    QSpinBox *port;
    QLineEdit *database;
    QLineEdit *login;
    QLineEdit *password;
};

class EndPage : public QWizardPage
{
    Q_OBJECT

public:
    EndPage(QWidget *parent = 0);

    int nextId() const;

private:
    QLabel *label;
    QCheckBox *checkBox;
};

#endif // DBCONNEXIONWIZARD_H
