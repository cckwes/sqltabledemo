#ifndef TABLEDLG_H
#define TABLEDLG_H

#include <QDialog>

#include <QSqlError>

class QTableView;
class QSqlRelationalTableModel;
class AddPersonDlg;

class TableDlg : public QDialog
{
    Q_OBJECT
public:
    explicit TableDlg(QWidget *parent = 0);
    ~TableDlg();

    QSqlError initDB();

signals:

public slots:
    void onAddEntry();
    void onAdded();
    void onRemoveEntry();

private:
    QTableView *personTable;
    QSqlRelationalTableModel *model;
    QPushButton *addBtn;
    QPushButton *removeBtn;

    AddPersonDlg *addDlg;
};

#endif // TABLEDLG_H
