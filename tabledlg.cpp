#include <QMessageBox>
#include <QTableView>
#include <QPushButton>
#include <QLayout>

#include <QVariant>
#include <QDebug>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRelationalTableModel>

#include "addpersondlg.h"
#include "tabledlg.h"

TableDlg::TableDlg(QWidget *parent) :
    QDialog(parent)
{
    if (!QSqlDatabase::drivers().contains("QSQLITE"))
    {
        QMessageBox::critical(this, "No SQLITE drier!", "It appears that you don't have a SQLITE driver in your system! Stopping...", QMessageBox::Ok, QMessageBox::NoButton);
        return;
    }

    QSqlError err = initDB();

    if (err.type() != QSqlError::NoError)
    {
        qDebug() << "Error initializing tables";
        qDebug() << err.text();
        return;
    }

    personTable = new QTableView(this);

    addBtn = new QPushButton("&Add", this);
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(addBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(personTable);
    mainLayout->addLayout(btnLayout);
    setLayout(mainLayout);

    setFixedSize(800, 600);

    model = new QSqlRelationalTableModel(this);
    model->setTable("person");

    int jobIdx = model->fieldIndex("job");
    int deptIdx = model->fieldIndex("department");

    model->setRelation(jobIdx, QSqlRelation("jobTitle", "id", "title"));
    model->setRelation(deptIdx, QSqlRelation("department", "id", "title"));

    model->setHeaderData(model->fieldIndex("id"), Qt::Horizontal, "ID");
    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, "Name");
    model->setHeaderData(model->fieldIndex("age"), Qt::Horizontal, "age");
    model->setHeaderData(jobIdx, Qt::Horizontal, "Job Title");
    model->setHeaderData(deptIdx, Qt::Horizontal, "Department");

    if (!model->select())
        qDebug() << model->lastError().text();

    personTable->setModel(model);
    personTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    addDlg = new AddPersonDlg(this);

    connect(addBtn, SIGNAL(clicked()), SLOT(onAddEntry()));
    connect(addDlg, SIGNAL(accepted()), SLOT(onAdded()));
}

TableDlg::~TableDlg()
{
}

void TableDlg::onAddEntry()
{
    addDlg->clearEntries();
    addDlg->exec();
}

void TableDlg::onAdded()
{
    QSqlQuery q;

    //won't insert any field checking here as the dialog should have check the
    //entries before accepted

    if (!q.prepare(QLatin1String("insert into person(name, age, job, department) values(?, ?, ?, ?)")))
    {
        qDebug() << "Database error while prepare for insertion: " << q.lastError().text();
        return;
    }

    q.addBindValue(addDlg->getName());
    q.addBindValue(addDlg->getAge());
    q.addBindValue(addDlg->getJobID());
    q.addBindValue(addDlg->getDeptID());

    if (!q.exec())
    {
        qDebug() << "Database error when insertion: " << q.lastError().text();
        return;
    }

    model->select();
}

QSqlError TableDlg::initDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":person:");

    if (!db.open())
        return db.lastError();

    QStringList tables = db.tables();

    if (tables.contains("person", Qt::CaseInsensitive) && tables.contains("jobTitle", Qt::CaseInsensitive) && tables.contains("department", Qt::CaseInsensitive))
    {
        qDebug() << "Tables ready!";
        return QSqlError();
    }

    QSqlQuery q;

    if (!q.exec(QLatin1String("create table person(id integer primary key autoincrement, name varchar, age integer, job integer, department integer)")))
        return q.lastError();

    if (!q.exec(QLatin1String("create table jobTitle(id integer primary key autoincrement, title varchar)")))
        return q.lastError();

    if (!q.exec(QLatin1String("create table department(id integer primary key autoincrement, title varchar)")))
        return q.lastError();

    qDebug() << "table created successfully";

    if (!q.exec(QLatin1String("insert into jobTitle(title) values('Manager')")))
        return q.lastError();
    int managerId = q.lastInsertId().toInt();

    if (!q.exec(QLatin1String("insert into jobTitle(title) values('Hardware Engineer')")))
        return q.lastError();
    int hEngId = q.lastInsertId().toInt();

    if (!q.exec(QLatin1String("insert into jobTitle(title) values('Sofware Engineer')")))
        return q.lastError();
    int sEngId = q.lastInsertId().toInt();

    if (!q.exec(QLatin1String("insert into department(title) values('R&D')")))
        return q.lastError();
    int rndId = q.lastInsertId().toInt();

    if (!q.exec(QLatin1String("insert into department(title) values('Engineering')")))
        return q.lastError();
    int engId = q.lastInsertId().toInt();

    if (!q.prepare(QLatin1String("insert into person(name, age, job, department) values(?, ?, ?, ?)")))
        return q.lastError();

    q.addBindValue("Tom Sneijer");
    q.addBindValue(34);
    q.addBindValue(hEngId);
    q.addBindValue(engId);
    if (!q.exec())
        return q.lastError();

    q.addBindValue("Wayne Huddlestone");
    q.addBindValue(28);
    q.addBindValue(sEngId);
    q.addBindValue(rndId);
    if (!q.exec())
        return q.lastError();

    q.addBindValue("Wesley Buemi");
    q.addBindValue(38);
    q.addBindValue(managerId);
    q.addBindValue(rndId);
    if (!q.exec())
        return q.lastError();

    q.addBindValue("Thomas Liu");
    q.addBindValue(32);
    q.addBindValue(managerId);
    q.addBindValue(engId);
    if (!q.exec())
        return q.lastError();

    return QSqlError();
}
