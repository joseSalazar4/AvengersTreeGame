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
    int rangoNombres1, rangoNombres2,  rangoApellidos1, rangoApellidos2,
    rangoProfesiones1,  rangoProfesiones2, rangoCreencias1, rangoCreencias2,
    rangoPaises1, rangoPaises2, generacion;

    Mundo();

    //SUPERHEROES
    QString antMan();
    QString thor(int);
    QString ironMan();
    QString spiderMan();

    //Villanos
    QString midnight();
    QString nebula(int);
    QString blackDwarf();
    QString ebonyMaw(int);
    QString corvusGlaive();

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
