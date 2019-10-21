#include "creadorpersonas.h"
#include "ui_creadorpersonas.h"

creadorPersonas::creadorPersonas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::creadorPersonas)
{
    ui->setupUi(this);
}

creadorPersonas::~creadorPersonas()
{
    delete ui;
}
