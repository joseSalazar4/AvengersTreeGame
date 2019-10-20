//
// Created by jose on 10/16/19.
//

#ifndef AVENGERS_TREE_GAME_PERSONA_H
#define AVENGERS_TREE_GAME_PERSONA_H


#include "ListaSimple.h"

struct Persona {
    int edad;
    QString ID, nombre, apellido, genero, creencia,profesion,
    fechaNacimiento,estadoMarital, continente, pais;
    ListaSimple * familia, amigos;
    ListaSimple * paises; //CREAR LISTA PAISES? USAR TEMPLATE
    //salud es algo que falta pero definir como

    Persona * siguiente, * anterior;
    Persona(){
        siguiente = anterior = nullptr;
    }


};


#endif //AVENGERS_TREE_GAME_PERSONA_H
