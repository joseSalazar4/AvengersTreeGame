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
    AVL<Persona>*arbolCompleto = new AVL<Persona>();
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
    QString ironManAux(Persona*, QString);
    QString antMan(int);
    QString spiderMan();

    //Villanos
    QString thanosAnnoYNivel(int anno, int nivel);
    QString thanosNivel(int nivel);
    QString thanosAnno(int anno);
    void thanosCrearHashTable();

    QString midnight();
    QString nebula();
    QString nebulaAux(Persona*);
    QString ebonyMaw(int);
    QString ebonyMawAux(Persona*victima, QString progenitorId);
    QString corvusGlaive();
    QString blackDwarf(int,QString);


    QString terminarPartida();

    //Pecados ^ Buenas Acciones
    void hacerlesPecar(Persona* persona);  //recorrer la lista de personas y darles qrandom a cada una de las personas.
    void hacerBuenasAcciones(Persona* persona);

    //Generaciones
    void crearPersona();
    void crearPoblacion(int);
    void asignarAmigos(Persona*);
    void asignarFamilia(Persona*);

    //Archivos
    QString crearTxtTiempo();
    QString crearLog(Persona *);
    QString escribirArchivo(std::string);
    void leerArchivo(QString nombreArchivo,QString datosRecolectados[]);

    //Vida Personas
    bool existeAmigo(Persona *);
    void vivirExperiencias(Persona *);
    void encontrarContinente(Persona *  );
    bool verificarValidezHijos(Persona * supuestoPadre, Persona * supuestoHijo);

    //Consultas (Heroes y Villanos)
    QString consultarSalvaciones();
    QString consultarEliminaciones();
    QString consultarEstadosHumanos();
    QString consultarDeporte(QString);
    QString consultarHumanoID(QString ID);
    QString consultarFamiliaID(QString ID);
    QString consultarAmigosAmigos(QString ID);

    //Insercion en arbol completo
    void insertarEnArbol();
    void completarArbol(QList<Persona*> * lista, Nodo<Persona> * nodo, int min, int max);
    QList<Persona*> * listaOrdenada();

    //Ordenamiento de Lista
    int obtainPivot(QList<Persona*>* lista, int min, int max);
    void quickSortFunction(QList<Persona*> * lista, int min, int max);
    void quickSort(QList<Persona*> * lista);


    //Devuelve una persona Random de la lista Principal
    int generateRandom(int min, int max);
    NodoDoble<Persona> * getPersonaRandom();
    QString thanosLogKill(QList<Persona*> *, QString m, int , int);

};

#endif // MUNDO_H
