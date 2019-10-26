#ifndef MUNDO_H
#define MUNDO_H

//#include "smtp.h"

#include <ctime>
#include <string>
#include <fstream>
#include <iostream>
#include <QTextStream>
#include "Deportes.h"
#include "Longevidad.h"
#include "registroIDs.h"
#include "templateAVL.h"
#include "templateLista.h"
//Pecados
//NoPecados (BuenasAcciones)

class Mundo {

public:
    AVL<Persona> * arbolMundo;
    Deportes * deportes = new Deportes();
    ListaDoble<Persona> * listaPersonasTotales;
    Longevidad * longevidad = new Longevidad();
    RegistroIds * registroIds = new RegistroIds();
    QString nombresHombres[499], nombresMujeres[499], apellidos[999], paises[99], creencias[13], profesiones[55];

    int generacion;

    Mundo();

    //SUPERHEROES
    void thor();
    void antMan();
    void ironMan();
    void spiderMan();

    //Villanos
    void midnight();
    void nebula(int);
    void blackDwarf();
    void ebonyMaw(int);
    void corvusGlaive();

    //Pecados ^ Buenas Acciones
    void hacerlesPecar(Persona* persona);  //recorrer la lista de personas y darles qrandom a cada una de las personas.
    void hacerBuenasAcciones(Persona* persona);

    //Generaciones
    void crearPersona();
    void crearPoblacion(int);
    void asignarAmigos(Persona*);
    void asignarFamilia(Persona*);

    //Archivos
    QString escribirArchivo(std::string);
    void leerArchivo(QString nombreArchivo,QString datosRecolectados[]);


    //
    bool existeAmigo(Persona *);

};

#endif // MUNDO_H
