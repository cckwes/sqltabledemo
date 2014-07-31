#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QLayout>
#include "addpersondlg.h"

AddPersonDlg::AddPersonDlg(QWidget *parent) :
    QDialog(parent)
{
    okBtn = new QPushButton("&Ok", this);
    cancelBtn = new QPushButton("&Cancel", this);

    nameEdit = new QLineEdit(this);
    ageEdit = new QLineEdit(this);

    jobCombo = new QComboBox(this);
    deptCombo = new QComboBox(this);

    nameLabel = new QLabel("Name: ", this);
    ageLabel = new QLabel("Age: ", this);
    jobLabel = new QLabel("Job Title: ", this);
    deptLabel = new QLabel("Department: ", this);

    QGridLayout *formLayout = new QGridLayout();
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
}
