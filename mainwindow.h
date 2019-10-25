#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "smtp.h"
#include "fstream"
#include "iostream"
#include "Persona.h"
#include "creadorpersonas.h"

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    creadorPersonas ventanaCrearPersonas;


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
    void on_btnEnviarCorreo_clicked();
    void on_btnBuenasAcciones_clicked();
    void on_btnGenerarPersonas_clicked();
    void on_btnGenerarPersonas_Finished(int,int,int,int,int,int,int,int,int,int);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
