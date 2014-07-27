#include <QApplication>
#include "tabledlg.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    TableDlg tdlg;
    tdlg.show();

    return app.exec();
}
