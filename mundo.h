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
#include "Heap.h"
#include "MundoThanos.h"
//Pecados
//NoPecados (BuenasAcciones)

class Mundo {

public:
    AVL<Persona> * arbolMundo;
    Deportes * deportes = new Deportes();
    ListaDoble<Persona> * listaPersonasTotales;
    Heap * heapPecados;
    Heap * heapBuenasAcciones;
    Longevidad * longevidad = new Longevidad();
    RegistroIds * registroIds = new RegistroIds();
    QList<QList<QString>> * continentes = new QList<QList<QString>>();
    MundoThanos * Thanos;

    QList<QString> * asia, *america,* africa, *oceania, *europa, * listaEliminados,
    * eliminacionesNebula,* eliminacionesCorvusGlaive,*eliminacionesBlackD,
    * eliminacionesEbonyMaw,* eliminacionesMidnight,*salvacionesIronMan,
    *salvacionesAntMan,* salvacionesSpiderMan, *salvacionesThor;

    QString nombresHombres[499], nombresMujeres[499], apellidos[999],
    paises[99],creencias[13], profesiones[55];

    int rangoNombres1, rangoNombres2,  rangoApellidos1, rangoApellidos2,rangoProfesiones1,
    rangoProfesiones2, rangoCreencias1, rangoCreencias2, cantSalvados,
    rangoPaises1, rangoPaises2, generacion, cantAsesinados;

    Mundo();

    //SUPERHEROES
    QString thor(int);
    QString ironMan();
    QString antMan(int);
    QString spiderMan();

    //Villanos
    QString thanos();
    QString midnight();
    QString nebula(int);
    QString ebonyMaw(int);
    QString corvusGlaive();
    QString blackDwarf(int,QString);

    //Pecados ^ Buenas Acciones
    void hacerlesPecar(Persona* persona);  //recorrer la lista de personas y darles qrandom a cada una de las personas.
    void hacerBuenasAcciones(Persona* persona);

    //Generaciones
    void crearPersona();
    void crearPoblacion(int);
    void asignarAmigos(Persona*);
    void asignarFamilia(Persona*);

    //Archivos
    QString crearLog(Persona *);
    QString escribirArchivo(std::string);
    void leerArchivo(QString nombreArchivo,QString datosRecolectados[]);
    QString crearTxtTiempo();

    //Vida Personas
    bool existeAmigo(Persona *);
    bool verificarValidezHijos(Persona * supuestoPadre, Persona * supuestoHijo);
    void vivirExperiencias(Persona *);
    void encontrarContinente(Persona *  );

    //Consultas (Heroes y Villanos)
    QString consultarSalvaciones();
    QString consultarEliminaciones();


    //Devuelve una persona Random de la lista Principal
    NodoDoble<Persona> * getPersonaRandom();
    int generateRandom(int min, int max);

};

#endif // MUNDO_H
