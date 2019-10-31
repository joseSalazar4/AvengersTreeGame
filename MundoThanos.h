#ifndef MUNDOTHANOS_H
#define MUNDOTHANOS_H
#include <QList>
#include "Persona.h"
struct MundoThanos{
    QList<Persona*> * mundo[65][10];
    int promedio;

public:
    MundoThanos(){
        for(int i=0; i<54; i++){
            for(int j=0; i<9; i++){
                mundo[i][j] = nullptr; //new QList<Persona*>;
            }
        }
        promedio = 0;
    }

    void agregarPersona(Persona * persona){
        int ibnp = IBNP(persona);
        int i = persona->edad;
        int j = obtenerIndice(ibnp);

        if(mundo[i][j] == nullptr) mundo[i][j] = new QList<Persona*>();
        mundo[i][j]->append(persona);
    }

    //Ingrese el año que Thanos nuestro salvador quiere dar por sacrificio para equilibrar nuestro hermoso mundo.
    //Solo los nacidos entre el año 1954 y 2019 son dignos para dar en sacrificio. Benditos sean. De no ser así le devolveremos un nullptr
    //Le entregamos a nuestro Thanos elimininadosXThanos para que el se encargue del resto, Oh gran Thanos.
    QList<QList<Persona*>*> * matarPorAnno(int anno){
        if(anno <= 2019 && anno > 1954){
            int listaIndex = 2019-anno;
            QList<QList<Persona*>*> * eliminadosXThanos = new QList<QList<Persona*>*>();
            for(int j=0; j<10; j++)
                eliminadosXThanos->append(mundo[listaIndex][j]);
            return eliminadosXThanos;
        }
        return nullptr;
    }

    //Ingrese el Nivel que Thanos nuestro salvador quiere dar por sacrificio para equilibrar nuestro hermoso mundo.
    //Solo los niveles entre 0 y 9 son dignos para dar en sacrificio. Benditos sean. De no ser así le devolveremos un nullptr
    //Le entregamos a nuestro Thanos elimininadosXThanos para que él se encargue del resto, Oh gran Thanos.
    QList<QList<Persona*>*> * matarPorNivel(int nivel){
        if(nivel <= 9 && nivel > 0){
            QList<QList<Persona*>*> * eliminadosXThanos = new QList<QList<Persona*>*>();
            for(int i=0; i<65; i++)
                eliminadosXThanos->append(mundo[i][nivel]);
            return eliminadosXThanos;
        }
        return nullptr;
    }

    QList<Persona*> * matarPorAnnoYNivel(int anno, int nivel){
        if(anno <= 2019 && anno > 1954){
            if(nivel <= 9 && nivel > 0){
                int listaIndex = 2019-anno;
                QList<Persona*> * eliminadosXThanos;
                eliminadosXThanos = mundo[listaIndex][nivel];
                return eliminadosXThanos;
            }
        }
        return nullptr;
    }


    //IBNP = Indice de buenas personas.
    int IBNP(Persona * persona){
        int b =     (persona->pecadosTotales - persona->buenasAccionesTotales)
                   + persona->paisesVisitados->size() + persona->ctdEjercicioxSemana/persona->deportes->size()
                   - persona->hijos->size() + persona->amigos->size() - persona->edad + 500;

        promedio += b;
        return b;
    }

    int obtenerIndice(int ibnp){
        if(ibnp < 300) return 0;
        else if(ibnp>=300 && ibnp <350) return 1;
        else if(ibnp>=350 && ibnp <400) return 2;
        else if(ibnp>=400 && ibnp <450) return 3;
        else if(ibnp>=450 && ibnp <500) return 4;
        else if(ibnp>=500 && ibnp <550) return 5;
        else if(ibnp>=550 && ibnp <600) return 6;
        else if(ibnp>=600 && ibnp <650) return 7;
        else if(ibnp>=700 && ibnp <750) return 8;
        else return 9;

    }




};

#endif // MUNDOTHANOS_H
