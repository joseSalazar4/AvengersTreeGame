#include "mainwindow.h"
#include <QApplication>

using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //std::string s = date::format("%F %T", std::chrono::system_clock::now());
    return a.exec();
}
