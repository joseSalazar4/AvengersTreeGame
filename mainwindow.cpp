#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "smtp.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    Smtp* smtp = new Smtp("mikomeka1@gmail.com", "mikomeka11", "smtp.gmail.com", 465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    QList<QString> archivos = {"example.txt"};

    smtp->sendMail("mikomeka1@gmail.com", "jsalazarg48@gmail.com" , "No no o quiero ver","ESto es \n solo una \n prueba para ver si los enters funcionan", archivos);

}
