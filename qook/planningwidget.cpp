#include "planningwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QtDebug>
#include <QSqlQuery>
#include <QVariant>
#include <QDialogButtonBox>
#include "mealview.h"

PlanningWidget::PlanningWidget(QWidget *parent) : QWidget(parent)
{
}

PlanningWidget::PlanningWidget(QDate from, QDate to, QWidget *parent) : QWidget(parent), from(from), to(to)
{
    init();
}

void PlanningWidget::init()
{
    if (!from.isValid() || !to.isValid() || from > to)
        return;

    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    QHBoxLayout *layout = new QHBoxLayout();
    mainLayout->addLayout(layout);


    QSqlQuery query;
    QFrame *line;
    for (QDate current = from; current <= to; current = current.addDays(1))
    {
        QVBoxLayout *subLayout = new QVBoxLayout();
        QLabel *label = new QLabel();
        label->setText(current.toString(Qt::SystemLocaleShortDate));
        label->setAlignment(Qt::AlignCenter);
        subLayout->addWidget(label);

        for (int moment = 0; moment <= 1; moment++)
        {
            query.prepare("select id from meals where date=:date and moment=:moment");
            query.bindValue(":date", current);
            query.bindValue(":moment", moment);
            query.exec();
            int id;
            if (query.next())
            {
                id = query.value(0).toInt();
            }
            else
            {
                // Create row
                query.prepare("insert into meals values(:id, :date, :moment, :number)");
                query.bindValue(":id", QVariant(QVariant::Int));
                query.bindValue(":date", current);
                query.bindValue(":moment", moment);
                query.bindValue(":number", 1);
                query.exec();

                // Take the new id
                query.prepare("select id from meals where date=:date and moment=:moment");
                query.bindValue(":date", current);
                query.bindValue(":moment", moment);
                query.exec();
                query.next();
                id = query.value(0).toInt();
            }

            subLayout->addWidget(new MealView(id));

    }

        layout->addLayout(subLayout);

        line = new QFrame();
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        layout->addWidget(line);
    }
    layout->removeWidget(line);
    line->deleteLater();

    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->setStandardButtons(QDialogButtonBox::Close);
    buttonBox->setCenterButtons(false);
    connect(buttonBox, SIGNAL(rejected()),
            this, SIGNAL(close()));
    mainLayout->addWidget(buttonBox);
}
