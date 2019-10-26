#ifndef LONGEVIDAD_H
#define LONGEVIDAD_H
#include <QList>
#include "Persona.h"

//Use el metodo obtenerFecha despues de haberle asignado una fechaNacimiento a la persona.
//Este le deuelve un entero con su respectiva edad y además lo agrega a la lista de Personas de su rango Etario.

struct Longevidad{
    QList<QList<Persona*>*> tablaRangoEtario[9];

public:
    int obtenerEdad(Persona*);
private:
    int fHash(int edad);
    void agregarARangoEtario(Persona*, int);

};


int Longevidad::obtenerEdad(Persona *persona){
    return persona->fechaNacimiento->anno - 2019;
}

int Longevidad::fHash(int edad){
    if(edad >= 0 && edad <= 1) return 0;
    else if(edad >= 2 && edad <= 4) return 1;
    else if(edad >= 5 && edad <= 10) return 2;
    else if(edad >= 10 && edad <= 14) return 3;
    else if(edad >= 15 && edad <= 19) return 4;
    else if(edad >= 20 && edad <= 24) return 5;
    else if(edad >= 25 && edad <= 34) return 6;
    else if(edad >= 35 && edad <= 64) return 7;
    else return 8;
}

void Longevidad::agregarARangoEtario(Persona *persona, int edad){
    int index = fHash(edad);
    tablaRangoEtario->at(index)->append(persona);
}

#endif // LONGEVIDAD_H
