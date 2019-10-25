#ifndef CREADORPERSONAS_H
#define CREADORPERSONAS_H

#include <QDialog>

namespace Ui {
class creadorPersonas;
}

class creadorPersonas : public QDialog
{
    Q_OBJECT

public:
    explicit creadorPersonas(QWidget *parent = nullptr);
    ~creadorPersonas();

private slots:
    void on_pushButton_clicked();

    void on_btnGenerarPersonas_clicked();

signals:
    void finalizo(int rangoNomb1,int rangoNomb2,int rangoApellidos1,int rangoApellidos2, int rangoProf1,int rangoProf2,int rangoCreencias1,int rangoCreencias2,int rangoPaises1,int rangoPaises2);

private:
    Ui::creadorPersonas *ui;
};

#endif // CREADORPERSONAS_H
