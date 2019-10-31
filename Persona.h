//
// Created by jose on 10/16/19.
//

#ifndef AVENGERS_TREE_GAME_PERSONA_H
#define AVENGERS_TREE_GAME_PERSONA_H

#include "FechaNacimiento.h"
#include <QList>

struct Persona {
    QList<QString> * deportes, *paisesVisitados , *logMuerte, *logSalvacion;
    bool vivo;
    Persona *padre, *madre, *pareja;
    FechaNacimiento * fechaNacimiento;
    QList<Persona*> * hijos, * amigos;
    QString ID, nombre, apellido, genero, creencia,profesion,estadoMarital, continente, pais;
    int edad, ctdEjercicioxSemana, pecados[6], buenasAcciones[6], pecadosTotales, buenasAccionesTotales;

    Persona(){

        vivo = true;
        ID = nombre = apellido = genero = creencia =
        profesion = estadoMarital = continente = pais = "";

        fechaNacimiento = nullptr;
        hijos = new QList<Persona*>;
        amigos = new QList<Persona*>;
        edad = ctdEjercicioxSemana = 0;
        logMuerte = new QList<QString>;
        logSalvacion= new QList<QString>;
        padre = madre = pareja  = nullptr;
        deportes = paisesVisitados = nullptr;
        paisesVisitados = new QList<QString>;

        for(int i = 0; i<7;i++) pecados[i] = 0;
        for(int i = 0; i<7;i++) buenasAcciones[i] = 0;

    }

};




#endif //AVENGERS_TREE_GAME_PERSONA_H
