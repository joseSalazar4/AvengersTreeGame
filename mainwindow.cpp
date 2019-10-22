#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Persona.h"

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
    Persona * tmp = new Persona();
    QString nombre  = tmp->escribirArchivo();
    Smtp* smtp = new Smtp("mikomeka1@gmail.com", "mikomeka11", "smtp.gmail.com", 465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    QList<QString> archivos = {nombre};

    smtp->sendMail("mikomeka1@gmail.com", "jsalazarg48@gmail.com" , "ASUNTO DEL CORREO ENVIADO","CUERPO DEL CORREO", archivos);

}

void MainWindow::on_btnEnviarCorreo_clicked()
{
    Persona * tmp = new Persona();
    QString nombre  = tmp->escribirArchivo();
    Smtp* smtp = new Smtp("mikomeka1@gmail.com", "mikomeka11", "smtp.gmail.com", 465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    QList<QString> archivos = {nombre};
    smtp->sendMail("mikomeka1@gmail.com", "jsalazarg48@gmail.com" , "ASUNTO DEL CORREO ENVIADO","CUERPO DEL CORREO", archivos);


}
