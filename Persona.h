//
// Created by jose on 10/16/19.
//

#ifndef AVENGERS_TREE_GAME_PERSONA_H
#define AVENGERS_TREE_GAME_PERSONA_H

#include "FechaNacimiento.h"

struct Persona {
    QList<QString> * deportes;
    Persona *padre, *madre, *pareja;
    FechaNacimiento * fechaNacimiento;
    QList<Persona*> * hijos, * amigos;
    QString ID, nombre, apellido, genero, creencia,profesion,estadoMarital, continente, pais;
    int edad, ctdEjercicioxSemana, pecados[6], buenasAcciones[6], pecadosTotales, buenasAccionesTotales;

    Persona(){
        ID = nombre = apellido = genero = creencia =
        profesion = estadoMarital = continente = pais = "";

        deportes = nullptr;
        fechaNacimiento = nullptr;
        edad = ctdEjercicioxSemana = pecadosTotales =buenasAccionesTotales = 0;

        hijos = amigos = nullptr;
        padre = madre = pareja = nullptr;
    }
};


#endif //AVENGERS_TREE_GAME_PERSONA_H
