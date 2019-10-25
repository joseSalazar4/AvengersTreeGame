#ifndef MUNDO_H
#define MUNDO_H

#include "Persona.h"
#include "templateABB.h"
#include "templateAVL.h"
#include "templateLista.h"

class Mundo {

public:
    ListaDoble<Persona> * listaPersonasTotales;
    AVL<Persona> * arbolMundo; //Tal vez deba ser otro tipo de tipo

    QString arrayNombresHombres[499], arrayNombresMujeres[499], ArrayApellidos[999], ArrayPaises[99], ArrayCreencias[13], arrayProfesiones[55];

    Mundo();


    void thor();
    void nebula();
    void antMan();
    void ironMan();
    void midnight();
    void ebonyMaw();
    void spiderMan();
    void blackDwarf();
    void corvusGlaive();
    void hacerlesPegar();
    void hacerBuenasAcciones();
};

#endif // MUNDO_H
