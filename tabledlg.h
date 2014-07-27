#ifndef TABLEDLG_H
#define TABLEDLG_H

#include <QDialog>

#include <QSqlError>

class QTableView;
class QSqlRelationalTableModel;

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

private:
    QTableView *personTable;
    QSqlRelationalTableModel *model;
    QPushButton *addBtn;
};

#endif // TABLEDLG_H
