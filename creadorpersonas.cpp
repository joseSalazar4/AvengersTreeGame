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

    rangoNomb1 = ui->spinBoxNombres1->value();
    rangoNomb2 = ui->spinBoxNombres2->value();
    rangoProf1 = ui->spinBoxProfesiones1->value();
    rangoProf2 = ui->spinBoxProfesiones2->value();
    rangoPaises1 = ui->spinBoxPaises1->value();
    rangoPaises2 = ui->spinBoxPaises2->value();
    rangoApellidos1 = ui->spinBoxApellidos1->value();
    rangoApellidos2 = ui->spinBoxApellidos2->value();
    rangoCreencias1 = ui->spinBoxCreencias1->value();
    rangoCreencias2 = ui->spinBoxCreencias2->value();

    //envia los datos al mainwindow donde seran utilizados por las funciones de generacion
    emit finalizo(rangoNomb1,rangoNomb2,rangoApellidos1,rangoApellidos2, rangoProf1,rangoProf2, rangoCreencias1, rangoCreencias2, rangoPaises1, rangoPaises2);
}


//Eliminar depues
void creadorPersonas::on_pushButton_clicked(){

}
