#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "smtp.h"
#include "fstream"
#include "mundo.h"
#include "creadorpersonas.h"
#include "templateAVL.h"

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Mundo * mundo;
    creadorPersonas ventanaCrearPersonas;
    QStringList nombresDeportes = {"Futbol", "Basketball", "Boxeo",
    "Atletismo", "Natacion", "Golf", "Futbol Americano","Ultimate Frisbee"};
    int rangoNombres1, rangoNombres2,  rangoApellidos1, rangoApellidos2,
    rangoProfesiones1,  rangoProfesiones2, rangoCreencias1, rangoCreencias2,
    rangoPaises1, rangoPaises2;


    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void on_btnThor_clicked();
    void on_btnPecar_clicked();
    void on_btnNebula_clicked();
    void on_btnAntMan_clicked();
    void on_btnCorvusG_clicked();
    void on_btnIronMan_clicked();
    void on_btnEbonyMaw_clicked();
    void on_btnMidnight_clicked();
    void on_btnSpiderMan_clicked();
    void on_btnBlackDwarf_clicked();
    void on_btnBuenasAcciones_clicked();
    void on_btnGenerarPersonas_clicked();
    void enviarCorreo(QString nombre, QString nombre2);
    void on_btnGenerarPersonas_Finished(int,int,int,int,int,int,int,int,int,int,int);


    void on_btnConsultaEliminaciones_clicked();

    void on_btnConsultaSalvaciones_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
