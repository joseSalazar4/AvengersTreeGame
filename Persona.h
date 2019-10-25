//
// Created by jose on 10/16/19.
//

#ifndef AVENGERS_TREE_GAME_PERSONA_H
#define AVENGERS_TREE_GAME_PERSONA_H

#include <ctime>
#include <string>
#include <fstream>
#include <iostream>
#include <iostream>
#include <string>
#include <qfile.h>
#include <qlist.h>
#include <qdebug.h>
#include <qstring.h>
#include <QTextStream>
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

    QString escribirArchivo();
};


#endif //AVENGERS_TREE_GAME_PERSONA_H
