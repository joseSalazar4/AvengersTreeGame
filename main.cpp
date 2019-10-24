#include "mainwindow.h"
#include <QApplication>
#include "templateAVL.h"
#include "registroIDs.h"
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();




    return a.exec();
}
