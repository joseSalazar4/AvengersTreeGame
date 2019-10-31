#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Persona.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mundo = new Mundo();
    ventanaCrearPersonas.hide();
    ui->comboBoxDeportes->addItems(nombresDeportes);
    ui->SpinBoxNivelThanos->setRange(0,9);
    ui->spinBoxAnnoThanos->setRange(1954, 2019);
    connect(&ventanaCrearPersonas, SIGNAL(finalizo(int,int,int,int,int,int,int,int,int,int,int)), this, SLOT(on_btnGenerarPersonas_Finished(int,int,int,int,int,int,int,int,int,int, int)));
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
    int cantidadVeces = 0;
    cantidadVeces = ui->spinBoxBlackD->value();
    QString deporte = ui->comboBoxDeportes->currentText();

    //REESTABLECEMOS LOS VALORES ORIGINALES PARA SIGUIENTE ITERACION
    ui->spinBoxBlackD->setValue(1);
    ui->comboBoxDeportes->setCurrentIndex(0);
    enviarCorreo(mundo->blackDwarf(cantidadVeces,deporte),"Black Dwarf");
}

void MainWindow::on_btnEbonyMaw_clicked(){
    //El boton simplemente enviara el correo con el archivo de texto
    int ID = ui->spinBoxEbonyMaw->value();

    ui->spinBoxEbonyMaw->setValue(1);
    enviarCorreo(mundo->ebonyMaw(ID),"Ebony Maw");
}

void MainWindow::on_btnMidnight_clicked(){
    //El boton simplemente enviara el correo con el archivo de texto

    enviarCorreo(mundo->midnight(),"Midnight");
}

void MainWindow::on_btnCorvusG_clicked(){
    //El boton simplemente enviara el correo con el archivo de texto

    enviarCorreo(mundo->corvusGlaive(),"Corvus Glaive");
}

void MainWindow::on_btnNebula_clicked()
{
    int ID = ui->spinBoxNebula->value();

    ui->spinBoxNebula->setValue(1);
    //El boton simplemente enviara el correo con el archivo de texto
    enviarCorreo(mundo->nebula(ID),"Nebula");
}

void MainWindow::on_btnBuenasAcciones_clicked()
{
    NodoDoble<Persona> * persona = mundo->listaPersonasTotales->primerNodo;

    for(int i = 0;i<mundo->listaPersonasTotales->largo;i++){
        mundo->hacerBuenasAcciones(persona->dato);
        persona = persona->siguiente;
    }
}

void MainWindow::on_btnPecar_clicked()
{
    NodoDoble<Persona> * persona = mundo->listaPersonasTotales->primerNodo;

    for(int i = 0;i<mundo->listaPersonasTotales->largo;i++){
        mundo->hacerlesPecar(persona->dato);
        persona = persona->siguiente;
    }
}

void MainWindow::on_btnGenerarPersonas_Finished(int _rangoNomb1, int _rangoNomb2, int _rangoApellidos1,int _rangoApellidos2, int _rangoProf1, int _rangoProf2,int _rangoCreencias1,int _rangoCreencias2,int _rangoPaises1,int _rangoPaises2, int cantidadPersonas)
{
    //Eliminar lo de abajo y asi usarlas en los metodos

    mundo->rangoNombres1 = _rangoNomb1;
    mundo->rangoNombres2 = _rangoNomb2;
    mundo->rangoPaises1 =_rangoPaises1;
    mundo->rangoPaises2 =_rangoPaises2;
    mundo->rangoProfesiones1 = _rangoProf1;
    mundo->rangoProfesiones2 = _rangoProf2;
    mundo->rangoCreencias1 = _rangoCreencias1;
    mundo->rangoCreencias2 = _rangoCreencias2;
    mundo->rangoApellidos1 = _rangoApellidos1;
    mundo->rangoApellidos2 = _rangoApellidos2;

    ventanaCrearPersonas.hide();
    mundo->crearPoblacion(cantidadPersonas);
}

void MainWindow::on_btnAntMan_clicked()
{
    int cantHormigas =  ui->spinBoxAntMan->value();
    ui->spinBoxAntMan->setValue(1);
    //El boton simplemente enviara el correo con el archivo de texto

    enviarCorreo(mundo->antMan(cantHormigas),"Ant Man");
}

void MainWindow::on_btnThor_clicked()
{
    int nivel  = ui->spinBoxThor->value();
    ui->spinBoxThor->setValue(1);
    //El boton simplemente enviara el correo con el archivo de texto
    enviarCorreo(mundo->thor(nivel),"Thor");
}

void MainWindow::on_btnSpiderMan_clicked()
{
    //El boton simplemente enviara el correo con el archivo de texto
    enviarCorreo(mundo->spiderMan(),"Spider Man");
}

void MainWindow::on_btnIronMan_clicked()
{
    //El boton simplemente enviara el correo con el archivo de texto
    enviarCorreo(mundo->ironMan(),"Iron Man");
}

void MainWindow::on_btnGenerarPersonas_clicked()
{
    ventanaCrearPersonas.show();
}

void MainWindow::on_btnConsultaEliminaciones_clicked()
{
    enviarCorreo(mundo->consultarEliminaciones(), "Consulta Eliminaciones");
}

void MainWindow::on_btnConsultaSalvaciones_clicked()
{
    enviarCorreo(mundo->ironMan(),"Consulta Salvaciones");
}

void MainWindow::on_btnThanos_clicked()
{
    bool isNivel = ui->checkBoxNivelThanos->isChecked();
    bool isAnno = ui->checkBoxAnnoThanos->isChecked();
    int nivel = ui->SpinBoxNivelThanos->value();
    int anno = ui->spinBoxAnnoThanos->value();

    if(isNivel && isAnno){ //Busca eliminar Año y Nivel

    }
    else if(isNivel && !isAnno){ //Busca eliminar solo el nivel

    }
    else if(isAnno && !isNivel){ //Busca eliminar solo el año

    }
}
