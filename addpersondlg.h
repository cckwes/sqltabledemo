#ifndef ADDPERSONDLG_H
#define ADDPERSONDLG_H

#include <QDialog>

class QLineEdit;
class QPushButton;
class QComboBox;
class QLabel;

class AddPersonDlg : public QDialog
{
    Q_OBJECT
public:
    explicit AddPersonDlg(QWidget *parent = 0);

signals:

public slots:

private:
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QLineEdit *nameEdit;
    QLineEdit *ageEdit;
    QComboBox *jobCombo;
    QComboBox *deptCombo;

    QLabel *nameLabel;
    QLabel *ageLabel;
    QLabel *jobLabel;
    QLabel *deptLabel;
};

#endif // ADDPERSONDLG_H
