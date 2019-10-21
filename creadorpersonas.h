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

private:
    Ui::creadorPersonas *ui;
};

#endif // CREADORPERSONAS_H
