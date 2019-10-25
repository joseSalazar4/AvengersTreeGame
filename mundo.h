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
    QString arrayNombresHombres[499], arrayNombresMujeres[499], ArrayApellidos[999], ArrayPaises[99], ArrayCreencias[13], arrayProfesiones[55];

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
    void hacerlesPegar();
    void hacerBuenasAcciones();

    void crearPoblacion(int);

    void crearPersona();
    void asignarFamilia(Persona*);
    void asignarAmigos(Persona*);


};

#endif // MUNDO_H
