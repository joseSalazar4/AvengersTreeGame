#ifndef MUNDO_H
#define MUNDO_H

#include "Persona.h"
#include "templateAVL.h"
#include "templateLista.h"

#include "Deportes.h"
#include "Longevidad.h"
#include "FechaNacimiento.h"
#include "registroIDs.h"
//Pecados
//NoPecados (BuenasAcciones)

class Mundo {

public:
    ListaDoble<Persona> * listaPersonasTotales;
    AVL<Persona> * arbolMundo; //Tal vez deba ser otro tipo de tipo
    QString nombresHombres[499], nombresMujeres[499], apellidos[999], paises[99], creencias[13], profesiones[55];

    Deportes * deportes = new Deportes();
    Longevidad * longevidad = new Longevidad();
    RegistroIds * registroIds = new RegistroIds();


    int generacion;
    Mundo();

    void thor();
    void nebula();
    void antMan();
    void ironMan(); //Recorre el arbol, pregunta si ya pasó por ese nodo. Si no, hace random y depende del resultado salva ese nodo y lo pone true.
                    //Al terminar el proceso, restaura los valores de los nodos a false.
    void midnight();
    void ebonyMaw();
    void spiderMan();
    void blackDwarf();
    void corvusGlaive();
    void hacerlesPecar(Persona* persona);  //recorrer la lista de personas y darles qrandom a cada una de las personas.
    void hacerBuenasAcciones(Persona* persona);

    void crearPoblacion(int);

    void crearPersona();
    void asignarFamilia(Persona*);
    void asignarAmigos(Persona*);


};

#endif // MUNDO_H
