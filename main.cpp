#include "mainwindow.h"
#include <QApplication>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.mundo->escribirArchivo("Solo queiero \n intentar de que sea una de las mejores \n progras ever pero no siempre se puede fuck.");

    w.show();

    return a.exec();
}
