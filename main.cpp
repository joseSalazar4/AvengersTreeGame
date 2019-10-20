#include "mainwindow.h"
#include "iostream"
#include "fstream"
#include <QApplication>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    ofstream myfile;
    myfile.open ("example.txt");
    myfile << "Writing this to a file.\n";
    myfile << "NO me dejare vencer no los dejare llevarme.\n NUnca nadie meva a dominar no yo voy a pelear";
    myfile.close();

    return a.exec();
}
