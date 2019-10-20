//
// Created by jose on 10/12/19.
//

#include "ListaPersonas.h"

void ListaPersonas::insertarFinal(QString id, short number) {
    if (estaVacia()) {
        primerNodo = ultimoNodo = new Persona();
        largo++;
    }
    else {
        ultimoNodo->siguiente = new Persona();
        ultimoNodo->siguiente->anterior = ultimoNodo;
        ultimoNodo = ultimoNodo->siguiente;
        largo++;
    }
}

void ListaPersonas::insertarFinal(Persona * m) {
    if (estaVacia()) {
        primerNodo = ultimoNodo = m;
        largo++;
    }
    else {
        ultimoNodo->siguiente  = m;
        ultimoNodo->siguiente->anterior = ultimoNodo;
        ultimoNodo = ultimoNodo->siguiente;
        largo++;
    }
}


bool ListaPersonas::estaVacia(){
    return  primerNodo == nullptr;
}
