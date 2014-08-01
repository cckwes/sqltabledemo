#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QLayout>

#include <QIntValidator>
#include <QMessageBox>

#include <QSqlRelationalTableModel>
#include <QSqlError>
#include <QDebug>

#include "addpersondlg.h"

AddPersonDlg::AddPersonDlg(QWidget *parent) :
    QDialog(parent)
{
    //model
    jobModel = new QSqlRelationalTableModel(this);
    jobModel->setTable("jobTitle");
    jobModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    if (!jobModel->select())
    {
        qDebug() << "Load job model failed: " << jobModel->lastError().text();
        return;
    }

    deptModel = new QSqlRelationalTableModel(this);
    deptModel->setTable("department");
    deptModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    if (!deptModel->select())
    {
        qDebug() << "Load dept model failed: " << deptModel->lastError().text();
        return;
    }

    okBtn = new QPushButton("&Ok", this);
    okBtn->setDefault(true);
    cancelBtn = new QPushButton("&Cancel", this);

    nameEdit = new QLineEdit(this);
    ageEdit = new QLineEdit(this);
    QIntValidator *ageValidator = new QIntValidator(this);
    ageValidator->setRange(16, 80);
    ageEdit->setValidator(ageValidator);

    jobCombo = new QComboBox(this);
    jobCombo->setCurrentIndex(-1);
    jobCombo->setModel(jobModel);
    jobCombo->setModelColumn(1);

    deptCombo = new QComboBox(this);
    deptCombo->setCurrentIndex(-1);
    deptCombo->setModel(deptModel);
    deptCombo->setModelColumn(1);

    nameLabel = new QLabel("Name: ", this);
    ageLabel = new QLabel("Age: ", this);
    jobLabel = new QLabel("Job Title: ", this);
    deptLabel = new QLabel("Department: ", this);    QGridLayout *formLayout = new QGridLayout();
    formLayout->addWidget(nameLabel, 0, 0);
    formLayout->addWidget(nameEdit, 0, 1);
    formLayout->addWidget(ageLabel, 1, 0);
    formLayout->addWidget(ageEdit, 1, 1);
    formLayout->addWidget(jobLabel, 2, 0);
    formLayout->addWidget(jobCombo, 2, 1);
    formLayout->addWidget(deptLabel, 3, 0);
    formLayout->addWidget(deptCombo, 3, 1);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(okBtn);
    buttonLayout->addSpacing(10);
    buttonLayout->addWidget(cancelBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(formLayout);
    mainLayout->addSpacing(30);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connectSS();
}

void AddPersonDlg::clearEntries()
{
    nameEdit->setText(QString());
    ageEdit->setText(QString());
    jobCombo->setCurrentIndex(-1);
    deptCombo->setCurrentIndex(-1);
}

QString AddPersonDlg::getName() const
{
    return nameEdit->text();
}

int AddPersonDlg::getAge() const
{
    return ageEdit->text().toInt();
}

int AddPersonDlg::getJobID() const
{
    QModelIndex itemIndex = jobModel->index(jobCombo->currentIndex(), 0);
    return jobModel->data(itemIndex).toInt();
}

int AddPersonDlg::getDeptID() const
{
    QModelIndex itemIndex = deptModel->index(deptCombo->currentIndex(), 0);
    return deptModel->data(itemIndex).toInt();
}

void AddPersonDlg::connectSS()
{
    connect(okBtn, SIGNAL(clicked()), SLOT(onSubmit()));
    connect(cancelBtn, SIGNAL(clicked()), SLOT(onCancel()));
}

void AddPersonDlg::onSubmit()
{
    if (!nameEdit->text().isEmpty() && !ageEdit->text().isEmpty() && (jobCombo->currentIndex() != -1) && (deptCombo->currentIndex() != -1))
    {
        if (QMessageBox::question(this, "Confirmation", "Confirm adding this entry to database?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
        {
            emit accepted();
            this->close();
        }
    }
    else
    {
        QMessageBox::critical(this, "Incomplete Form", "One of more required field missing!", QMessageBox::Ok, QMessageBox::NoButton);
    }
}

void AddPersonDlg::onCancel()
{
    emit rejected();
    this->close();
}
