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

private:
    QTableView *personTable;
    QSqlRelationalTableModel *model;
};

#endif // TABLEDLG_H
