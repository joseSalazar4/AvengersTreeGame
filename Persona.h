//
// Created by jose on 10/16/19.
//


#ifndef AVENGERS_TREE_GAME_PERSONA_H
#define AVENGERS_TREE_GAME_PERSONA_H

#include <iostream>
#include <fstream>
#include <string>
#include "qfile.h"
#include "QTextStream"
#include "qlist.h"
#include <iostream>
#include "smtp.h"
#include <ctime>
#include"string"
#include "QRandomGenerator"
#include "qdebug.h"
#include "qstring.h"
#include "FechaNacimiento.h"

struct Persona {
    int edad, ctdEjercicioxSemana;
    FechaNacimiento * fechaNacimiento;
    QString ID, nombre, apellido, genero, creencia,profesion,estadoMarital, continente, pais;
    QList<QString> * deportes;
    QList<Persona*> * hijos;
    QList<Persona*> * amigos;
    Persona *padre, *madre, *pareja;
    //ListaSimple * familia, amigos;
    //ListaSimple * paises; //CREAR LISTA PAISES? USAR TEMPLATE
    //salud es algo que falta pero definir como

    Persona(){
        ID = nombre = apellido = genero = creencia =
        profesion = estadoMarital = continente = pais = "";

        fechaNacimiento = nullptr;
        deportes = nullptr;
        edad = ctdEjercicioxSemana = 0;

        hijos = amigos = nullptr;
        padre = madre = pareja = nullptr;

    }

    QString escribirArchivo();
};


#endif //AVENGERS_TREE_GAME_PERSONA_H
