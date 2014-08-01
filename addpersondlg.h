#ifndef ADDPERSONDLG_H
#define ADDPERSONDLG_H

#include <QDialog>

class QLineEdit;
class QPushButton;
class QComboBox;
class QLabel;
class QSqlRelationalTableModel;

class AddPersonDlg : public QDialog
{
    Q_OBJECT
public:
    explicit AddPersonDlg(QWidget *parent = 0);
    void clearEntries();

    QString getName() const;
    int getAge() const;
    int getJobID() const;
    int getDeptID() const;

signals:

public slots:
    void onSubmit();
    void onCancel();

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

    QSqlRelationalTableModel *jobModel;
    QSqlRelationalTableModel *deptModel;

    void connectSS();
};

#endif // ADDPERSONDLG_H
