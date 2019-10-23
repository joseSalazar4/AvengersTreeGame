#include "creadorpersonas.h"
#include "ui_creadorpersonas.h"

creadorPersonas::creadorPersonas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::creadorPersonas)
{
    //Utilizar stylesheet para cambiar colores de los labels y demas
    ui->setupUi(this);
}

creadorPersonas::~creadorPersonas()
{
    delete ui;
}

void creadorPersonas::on_btnGenerarPersonas_clicked()
{
    int rangoNomb1,rangoNomb2,rangoApellidos1,rangoApellidos2, rangoProf1,
            rangoProf2, rangoCreencias1, rangoCreencias2, rangoPaises1, rangoPaises2;

    rangoNomb1 = ui->lineEditNomb1->text().toInt();
    rangoNomb2 = ui->lineEditNomb2->text().toInt();
    rangoProf1 = ui->lineEditProf1->text().toInt();
    rangoProf2 = ui->lineEditProf2->text().toInt();
    rangoPaises1 = ui->lineEditPaises1->text().toInt();
    rangoPaises2 = ui->lineEditPaises2->text().toInt();
    rangoApellidos1 = ui->lineEditApellidos1->text().toInt();
    rangoApellidos2 = ui->lineEditApellidos2->text().toInt();
    rangoCreencias1 = ui->lineEditCreencias1->text().toInt();
    rangoCreencias2 = ui->lineEditCreencias2->text().toInt();

    //envia los datos al mainwindow donde seran utilizados por las funciones de generacion
    emit finalizo(rangoNomb1,rangoNomb2,rangoApellidos1,rangoApellidos2, rangoProf1,rangoProf2, rangoCreencias1, rangoCreencias2, rangoPaises1, rangoPaises2);
}


//Eliminar depues
void creadorPersonas::on_pushButton_clicked(){

}
