#include "dbconnexionwizard.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QFileDialog>
#include <QDesktopServices>
#include <QDir>
#include <QFileInfo>
#include <QStringList>
#include <QSqlDatabase>
#include <QSettings>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include <QtDebug>

DBConnexionWizard::DBConnexionWizard(QWidget *parent) :
    QWizard(parent)
{
    setPage(Page_Intro, new IntroPage);
    setPage(Page_DBChoice, new DBChoicePage);
    setPage(Page_SQLite, new SQLitePage);
    setPage(Page_OtherDB, new OtherDBPage);
    setPage(Page_End, new EndPage);

    setStartId(Page_Intro);

    setWindowTitle(tr("Database Choice Wizard"));
    setOption(QWizard::NoCancelButton, true);
}

void DBConnexionWizard::accept() {

    QSettings settings;

    if (hasVisitedPage(Page_SQLite))
    {
        settings.setValue("db/driver", "QSQLITE");
        settings.setValue("db/database", field("sqlite.database"));

    }
    else
    {
        settings.setValue("db/driver", QSqlDatabase::drivers().at(field ("driver").toInt()));
        settings.setValue("db/database", field("database"));
        settings.setValue("db/host", field("host"));
        settings.setValue("db/port", field("port"));
        settings.setValue("db/login", field("login"));
        settings.setValue("db/password", field("password"));
    }
    settings.setValue("db/keepInfo", true);
    settings.setValue("db/populate", field("populate"));
    QWizard::accept();
}

bool DBConnexionWizard::connectToDb()
{
    QSettings settings;
    if (!settings.value("db/keepInfo", false).toBool())
    {
        DBConnexionWizard wiz;
        wiz.exec();
    }
    QSqlDatabase db = QSqlDatabase::addDatabase(settings.value("db/driver").toString());
    db.setDatabaseName(settings.value("db/database").toString());
    db.setHostName(settings.value("db/host").toString());
    db.setPort(settings.value("db/port").toInt());
    db.setUserName(settings.value("db/login").toString());
    db.setPassword(settings.value("db/password").toString());

    if (db.driverName() == "QSQLITE" && db.databaseName() != ":memory:")
    {
        QFileInfo fileInfo(db.databaseName());
        QDir dir = fileInfo.dir();
        dir.mkpath(dir.absolutePath());

    }

    if (!db.open())
    {
        QMessageBox::critical(0, tr("Cannot open database"),
                              tr("Unable to establish a database connection.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }

    // Check if Qook's data are presents
    QSqlQuery versionQuery;
    versionQuery.exec("select * from qook");
    versionQuery.next();

    if (!versionQuery.isValid()) // There's no qook data here
    {
        QSqlQuery query;

        // Info about the database itself.
        query.exec("create table qook (value integer)");
        query.exec("insert into qook values (1)");
        
        query.exec("create table sections "       // Sections
                   "("
                   "(id integer primary key, "
                   "name text, "                  // Name
                   "position int"                 // Used to order the sections
                   ")");

        query.exec("create table ingredients "    // Ingredients
                   "("
                   "id integer primary key, "
                   "name text, "                // Name
                   "unit text, "                // How it's measured
                   "food bool, "                 // Whether or not it's food
                   "section int"                // Where it can be found
                   ")");

        query.exec("create table recipes "      // Recipes
                   "("
                   "id integer primary key, "
                   "name text, "                // Name
                   "description text, "         // Description
                   "category int"
                   ")");

        query.exec("create table categories "   // Categories
                   "("
                   "id integer primary key, "
                   "name text"                  // Name
                   ")");

        query.exec("create table meals "        // Meals
                   "("
                   "id integer primary key ,"
                   "date date, "                // Date
                   "moment int, "               // Moment of the day (0 for lunch, 1 for supper)
                   "number int"                 // Number of people eating
                   ")");

        query.exec("create table shoppinglists "// Shopping Lists
                   "("
                   "id integer primary key, "
                   "date date, "                // When are we shopping ?
                   "first int, "                // First meal included
                   "last int"                   // Last meal included
                   ")");

        query.exec("create table contains "     // The ingredients in a recipe
                   "("
                   "id integer primary key, "
                   "recipe int, "
                   "ingredient int, "
                   "amount real"                // How much
                   ")");

        query.exec("create table menu "         // The recipes at a meal
                   "("
                   "id integer primary key, "
                   "meal int, "
                   "recipe int"
                   ")");

        query.exec("create table extra "        // Extra stuff on the shopping list
                   "("
                   "id integer primary key, "
                   "ingredient int, "
                   "shoppinglist int, "
                   "amount real"                // How much
                   ")");

        query.exec("create table notneeded "        // Stuff on the shopping list that we don't need to buy
                   "("
                   "id integer primary key, "
                   "ingredient int, "
                   "shoppinglist int, "
                   "amount real"                // How much
                   ")");

        if (settings.value("db/populate").toBool())
        {
            populateDb();
            if (db.databaseName() != ":memory:")
                settings.setValue("db/populate", false);
        }
    }
    else
    {
        int version = versionQuery.value(0).toInt();
        if (version == 0)
            qDebug() << "Something bad happened when connecting to the database";
        else if (version > 1)
        {
            QMessageBox::critical(0, tr("Qook database too recent"),
                                  tr("This database has been created by a more recent version of Qook. "
                                     "Qook if closing"), QMessageBox::Cancel);
            settings.setValue("db/populate", false);
            return false;
        }
    }
    return true;
}

void DBConnexionWizard::populateDb()
{
    QStringList recipes;
    recipes << "Riz" << QString::fromUtf8("Pâtes") << QString::fromUtf8("Blé") << "Semoule" << "Pain";

    QSqlQuery query;
    query.prepare("insert into recipes values(:id, :name, :description, :category)");
    for (int i=0; i< recipes.size(); i++)
    {
        query.bindValue(":id", i);
        query.bindValue(":name", recipes.at(i));
        query.bindValue(":description", "");
        query.bindValue(":category",QVariant());
        query.exec();
    }
}

IntroPage::IntroPage(QWidget *parent) : QWizardPage(parent)
{
    setTitle(tr("Introduction"));

    label = new QLabel(tr("This wizard will help you configure the database "
                             "you want <i>Qook</i> to use"));
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

int IntroPage::nextId() const
{
    return DBConnexionWizard::Page_DBChoice;
}

DBChoicePage::DBChoicePage(QWidget *parent) : QWizardPage(parent)
{
    setTitle(tr("Database type choice"));

    label = new QLabel(tr("What type of database do you want to use ?"));
    label->setWordWrap(true);

    sqlite = new QRadioButton(tr("SQLite (recommended)"));
    other = new QRadioButton(tr("Another type"));
    sqlite->setChecked(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(sqlite);
    layout->addWidget(other);
    setLayout(layout);
}

int DBChoicePage::nextId() const
{
    if (sqlite->isChecked())
        return DBConnexionWizard::Page_SQLite;
    else
        return DBConnexionWizard::Page_OtherDB;
}

SQLitePage::SQLitePage(QWidget *parent) : QWizardPage(parent)
{
    setTitle(tr("SQLite configuration"));

    label = new QLabel(tr("Where should the database be saved ?"));
    defaultDB = new QRadioButton(tr("Use the default location (recommended)"));
    memory = new QRadioButton(tr("Save into memory (useful for testers)"));
    customLocation = new QRadioButton(tr("Save in a custom location"));

    locationEdit = new QLineEdit;
    locationButton = new QPushButton(tr("..."));
    QHBoxLayout *subLayout = new QHBoxLayout;
    subLayout->addWidget(locationEdit);
    subLayout->addWidget(locationButton);

    connect(defaultDB, SIGNAL(toggled(bool)),
            this, SLOT(onDefaultDB(bool)));
    connect(memory, SIGNAL(toggled(bool)),
            this, SLOT(onMemory(bool)));
    connect(customLocation, SIGNAL(toggled(bool)),
            this, SLOT(onCustomLocation(bool)));

    connect(locationButton, SIGNAL(clicked()),
            this, SLOT(onLocationButton()));

    defaultDB->setChecked(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(defaultDB);
    layout->addWidget(memory);
    layout->addWidget(customLocation);
    layout->addLayout(subLayout);
    setLayout(layout);

    registerField("sqlite.database", locationEdit);
}

void SQLitePage::onDefaultDB(bool /*toggle*/)
{
    locationEdit->setText(QDesktopServices::storageLocation(QDesktopServices::DataLocation)
                          + QDir::separator() + "database.sqlite");
    locationEdit->setEnabled(false);
    locationButton->setEnabled(false);
}

void SQLitePage::onMemory(bool /*toggle*/)
{
    locationEdit->setText(":memory:");
    locationEdit->setEnabled(false);
    locationButton->setEnabled(false);
}

void SQLitePage::onCustomLocation(bool /*toggle*/)
{
    locationEdit->setEnabled(true);
    locationButton->setEnabled(true);
}

void SQLitePage::onLocationButton()
{
    locationEdit->setText(QFileDialog::getSaveFileName(this, tr("Where to save the database ?")));
}

int SQLitePage::nextId() const
{
    return DBConnexionWizard::Page_End;
}
OtherDBPage::OtherDBPage(QWidget *parent) : QWizardPage(parent)
{
    setTitle(tr("Custom database configuration"));

    label = new QLabel(tr("Please configure your database."));
    driver = new QComboBox;
    host = new QLineEdit;
    port = new QSpinBox;
    port->setRange(0,65536);
    database = new QLineEdit;
    login = new QLineEdit;
    password = new QLineEdit;

    driver->addItems(QSqlDatabase::drivers());

    registerField("driver", driver);
    registerField("host*", host);
    registerField("port*", port);
    registerField("database*", database);
    registerField("login", login);
    registerField("password", password);

    QFormLayout *form = new QFormLayout;
    form->addRow(tr("Driver :"), driver);
    form->addRow(tr("Host :"), host);
    form->addRow(tr("Port"), port);
    form->addRow(tr("Database :"), database);
    form->addRow(tr("Login :"), login);
    form->addRow(tr("Password :"), password);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addLayout(form);
    setLayout(layout);
}

int OtherDBPage::nextId() const
{
    return DBConnexionWizard::Page_End;
}
EndPage::EndPage(QWidget *parent) : QWizardPage(parent)
{
    setTitle(tr("Populate"));
    label = new QLabel(tr("Do you want to populate the database ?"));
    checkBox = new QCheckBox("Populate the database.");
    registerField("populate", checkBox);
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);
    layout->addWidget(label);
    layout->addWidget(checkBox);
}

int EndPage::nextId() const
{
    return -1;
}
