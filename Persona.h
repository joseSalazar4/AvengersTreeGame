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
struct Persona {
    int edad;
    QString ID, nombre, apellido, genero, creencia,profesion,
    fechaNacimiento,estadoMarital, continente, pais;
    //ListaSimple * familia, amigos;
    //ListaSimple * paises; //CREAR LISTA PAISES? USAR TEMPLATE
    //salud es algo que falta pero definir como

    Persona * siguiente, * anterior;
    Persona(){
        siguiente = anterior = nullptr;
    }

    QString escribirArchivo();
};


#endif //AVENGERS_TREE_GAME_PERSONA_H
