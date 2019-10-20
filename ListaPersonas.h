//
// Created by jose on 10/12/19.
//

#ifndef AVENGERS_TREE_GAME_LISTADOBLE_H
#define AVENGERS_TREE_GAME_LISTADOBLE_H

#include "Persona.h"

struct ListaPersonas {
    Persona * primerNodo, * ultimoNodo;
    ListaPersonas(){
        primerNodo = ultimoNodo = nullptr;
    };

    bool estaVacia();
    void insertarFinal(QString id, short number);
    void insertarFinal(Persona * persona);
};


#endif //AVENGERS_TREE_GAME_LISTADOBLE_H
