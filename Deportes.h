#ifndef DEPORTES_H
#define DEPORTES_H
#include <QList>
#include <QRandomGenerator>
#include "Persona.h"

//Use el metodo generarDeportes() a la hora de crear una persona y asignarle
//un puntero a una lista con los deportes que practica.

//Para agregar más deportes simplemente lo agrega en el QList nombresDeportes.

//Cada deporte tiene una lista de punteros a las personas que practican ese deporte.

//Con el metodo generarVecesxSemana simplemente le retorna un entero con el numero de
//veces que es persona practica un deporte. El rango es de 1 a 21.

struct Deportes{
    QList<QString> nombresDeportes = {"Futbol", "Basketball", "Boxeo", "Atletismo", "Natacion"};
    QList<QList<Persona*>*> * deportes;
    Deportes(){
        deportes = new QList<QList<Persona*>*>;
        for(int i= 0; i<nombresDeportes.size(); i++){
            deportes->append(new QList<Persona*>);
        }
    }
public:
    QList<QString> *generarDeportes(Persona*);
    int generarVecesxSemana();
private:
    int generateRandom(int, int);

};

QList<QString>* Deportes::generarDeportes(Persona *persona){
    QList<QString> * deportesPersona = new QList<QString>;
    int numeroDeportes = generateRandom(1, nombresDeportes.size()-1);

    for(int i=0; i<numeroDeportes; i++){
        QString dep;
        int deporteIndex;
        do{
            deporteIndex = generateRandom(0, nombresDeportes.size()-1);
            //Agregamos a la lista el deporte que practica la persona
            dep = nombresDeportes.at(deporteIndex);

        }while(deportesPersona->contains(dep));

        deportesPersona->append(dep);
        //Guardamos en la lista de ese deporte un puntero a la persona
        deportes->at(deporteIndex)->append(persona);

    }
    return deportesPersona;
}


int Deportes::generateRandom(int min, int max){
    std::uniform_int_distribution<int> dist(min, max);
    int numRandom = dist(*QRandomGenerator::global());
    return numRandom;
}

int Deportes::generarVecesxSemana(){
    return generateRandom(1, 21);
}


#endif // DEPORTES_H
