#include "mainwindow.h"
#include <QApplication>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    for(int i=0 ;i<90000 ; i++){
        qDebug()<<QRandomGenerator::global()->bounded(1,3);
    }
    return a.exec();
}
