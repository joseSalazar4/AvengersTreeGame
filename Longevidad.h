#ifndef LONGEVIDAD_H
#define LONGEVIDAD_H
#include <QList>
#include "Persona.h"

//Use el metodo obtenerFecha despues de haberle asignado una fechaNacimiento a la persona.
//Este le deuelve un entero con su respectiva edad y además lo agrega a la lista de Personas de su rango Etario.

struct Longevidad{
    QList<Persona*> * tablaRangoEtario[9];

public:
    Longevidad(){
        for(int i=0; i<9; i++)
            tablaRangoEtario[i] = new QList<Persona*>;
    }
    int obtenerEdad(Persona *persona){
        int edad = 2019 - persona->fechaNacimiento->anno;
        agregarARangoEtario(persona, edad);
        return edad;
    }

     bool validarEdadPareja(Persona* p, Persona*pareja){
        int rangoP = fHash(p->edad);
        int rangoPareja = fHash(pareja->edad);

        if(rangoPareja == rangoP || rangoPareja+1 == rangoP ||rangoPareja-1 == rangoP) return true;
        return false;
    }


int fHash(int edad){
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

private:
void agregarARangoEtario(Persona *persona, int edad){
    int index = fHash(edad);
    tablaRangoEtario[index]->append(persona);
}

};
#endif // LONGEVIDAD_H
