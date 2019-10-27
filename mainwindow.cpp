#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Persona.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ventanaCrearPersonas.hide();
    connect(&ventanaCrearPersonas, SIGNAL(finished(int,int,int,int,int,int,int,int,int,int)), this, SLOT(on_modificartiempo_finished(int,int,int,int,int,int,int,int,int,int)));
    mundo = new Mundo();
    ui->setupUi(this);
    //ui->comboBoxDeportes->setSizeAdjustPolicy(ui->comboBoxDeportes->AdjustToMinimumContentsLength);
    ui->comboBoxDeportes->addItems(nombresDeportes);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enviarCorreo(QString nombre,QString nombreCaracter){

    QList<QString> archivos = {nombre};
    Smtp* smtp = new Smtp("mikomeka1@gmail.com", "mikomeka11", "smtp.gmail.com", 465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    smtp->sendMail("mikomeka1@gmail.com", "jsalazarg48@gmail.com" , "Log de: "+nombreCaracter,
                   "He cumplido con lo solicitado, aca esta la informacion", archivos);
}

void MainWindow::on_btnBlackDwarf_clicked(){
    //El boton simplemente enviara el correo con el archivo de texto
    enviarCorreo(mundo->blackDwarf(),"Black Dwarf");
}

void MainWindow::on_btnEbonyMaw_clicked(){
    //El boton simplemente enviara el correo con el archivo de texto
    enviarCorreo(mundo->blackDwarf(),"Ebony Maw");
}

void MainWindow::on_btnMidnight_clicked(){
    //El boton simplemente enviara el correo con el archivo de texto
    enviarCorreo(mundo->blackDwarf(),"Midnight");
}

void MainWindow::on_btnCorvusG_clicked(){
    //El boton simplemente enviara el correo con el archivo de texto
    enviarCorreo(mundo->blackDwarf(),"Corvus Glaive");
}

void MainWindow::on_btnNebula_clicked()
{
    //El boton simplemente enviara el correo con el archivo de texto
    enviarCorreo(mundo->blackDwarf(),"Nebula");
}

void MainWindow::on_btnBuenasAcciones_clicked()
{
}

void MainWindow::on_btnPecar_clicked()
{
}


void MainWindow::on_btnGenerarPersonas_Finished(int _rangoNomb1, int _rangoNomb2, int _rangoApellidos1,int _rangoApellidos2, int _rangoProf1, int _rangoProf2,int _rangoCreencias1,int _rangoCreencias2,int _rangoPaises1,int _rangoPaises2, int cantidadPersonas)
{
    //Eliminar lo de abajo y asi usarlas en los metodos

    rangoNombres1 = _rangoNomb1;
    rangoNombres2 = _rangoNomb2;
    rangoPaises1 =_rangoPaises1;
    rangoPaises2 =_rangoPaises2;
    rangoProfesiones1 = _rangoProf1;
    rangoProfesiones2 = _rangoProf2;
    rangoCreencias1 = _rangoCreencias1;
    rangoCreencias2 = _rangoCreencias2;
    rangoApellidos1 = _rangoApellidos1;
    rangoApellidos2 = _rangoApellidos2;

    mundo->crearPoblacion(cantidadPersonas);
    mundo->arbolMundo->imprimirArbol(); //Prueba
}

void MainWindow::on_btnAntMan_clicked()
{
    //El boton simplemente enviara el correo con el archivo de texto
    enviarCorreo(mundo->blackDwarf(),"Ant Man");
}

void MainWindow::on_btnThor_clicked()
{
    //El boton simplemente enviara el correo con el archivo de texto
    enviarCorreo(mundo->blackDwarf(),"Thor");
}

void MainWindow::on_btnSpiderMan_clicked()
{
    //El boton simplemente enviara el correo con el archivo de texto
    enviarCorreo(mundo->blackDwarf(),"Spider Man");
}

void MainWindow::on_btnIronMan_clicked()
{
    //El boton simplemente enviara el correo con el archivo de texto
    enviarCorreo(mundo->blackDwarf(),"Iron Man");
}

void MainWindow::on_btnGenerarPersonas_clicked()
{
    ventanaCrearPersonas.show();
    //Luego de mostrada podemos ver que se muestra la ventana
}

void MainWindow::on_comboBox_activated(const QString &opcion)
{
    int queNoSeOlvideAgregarElementos;
}
void MainWindow::on_btnEnviarCorreo_clicked(){

}
