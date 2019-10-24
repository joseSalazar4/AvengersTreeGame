#ifndef FECHANACIMIENTO_H
#define FECHANACIMIENTO_H
#include <QRandomGenerator>
#include <QString>

//Para agregar una fechaDeNacimiento a una persona solo agreguele un puntero a FechaNacimiento
// y hágale new.

struct FechaNacimiento{
    int dia, mes, anno;
    FechaNacimiento(){
        this->dia = generateRandom(1, 27);
        this->mes = generateRandom(1, 12);
        this->anno = generateRandom(1954, 2019);
    }
public:
    QString getFecha(){
        QString fecha;
        fecha = QString::number(dia)
                + "/" + QString::number(mes)
                + "/" + QString::number(anno);
        return fecha;
    }
private:
    int generateRandom(int min, int max){
        std::uniform_int_distribution<int> dist(min, max);
        int numRandom = dist(*QRandomGenerator::global());
        return numRandom;
    }

};

#endif // FECHANACIMIENTO_H
