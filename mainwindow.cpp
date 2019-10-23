#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Persona.h"
#include "creadorpersonas.h"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{

    ventanaCrearPersonas.hide();
    connect(&ventanaCrearPersonas, SIGNAL(finished(int,int,int,int,int,int,int,int,int,int)), this, SLOT(on_modificartiempo_finished(int,int,int,int,int,int,int,int,int,int)));
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::on_btnBlackDwarf_clicked()
{

}

void MainWindow::on_btnEbonyMaw_clicked()
{

}

void MainWindow::on_btnMidnight_clicked()
{

}

void MainWindow::on_btnCorvusG_clicked()
{

}

void MainWindow::on_btnNebula_clicked()
{

}

void MainWindow::on_btnBuenasAcciones_clicked()
{

}

void MainWindow::on_btnPecar_clicked()
{

}


void MainWindow::on_btnGenerarPersonas_clicked(int rangoNomb1, int rangoNomb2, int rangoApellidos1,int rangoApellidos2, int rangoProf1, int rangoProf2,int rangoCreencias1,int rangoCreencias2,int rangoPaises1,int rangoPaises2)
{
    //Eliminar lo de abajo y asi usarlas en los metodos
    ventanaCrearPersonas.show();

    /*rangoNomb1,rangoNomb2
    rangoApellidos1,rangoApellidos2
    rangoProf1, rangoProf2
    rangoCreencias1, rangoCreencias2
    rangoPaises1, rangoPaises2
    */


    //Aca se tuvo que pasar el  metodo ver en simulador el on_modificar y ver como lo paso.
    //Pruebe   Darle click y que haga algo idk. tuvo la convo?
}

void MainWindow::on_btnAntMan_clicked()
{

}

void MainWindow::on_btnThor_clicked()
{

}

void MainWindow::on_btnSpiderMan_clicked()
{

}

void MainWindow::on_btnIronMan_clicked()
{

}
