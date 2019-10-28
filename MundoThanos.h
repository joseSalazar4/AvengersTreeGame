#ifndef MUNDOTHANOS_H
#define MUNDOTHANOS_H
#include <QList>
#include "Persona.h"
struct MundoThanos{
    QList<Persona*> * mundo[54][9];

public:

    MundoThanos(){
        for(int i=0; i<54; i++){
            for(int j=0; i<9; i++){
                mundo[i][j] = new QList<Persona*>;
            }
        }
    }

private:

    int IBNP(Persona * persona){
        return     (persona->pecadosTotales - persona->buenasAccionesTotales)
                   + persona->paisesVisitados->size() + persona->ctdEjercicioxSemana/persona->deportes->size()
                   - persona->hijos->size() + persona->amigos->size() - persona->edad;

    }

    int obtenerIBNP(Persona * persona){
        int ibnp = IBNP(Persona* persona);

    }


};

#endif // MUNDOTHANOS_H
