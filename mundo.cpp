#include "mundo.h"

//Agregar metodo para enviar correos

Mundo::Mundo()
{
    listaPersonasTotales = new ListaDoble<Persona>();
    arbolMundo = new AVL<Persona>();
    generacion = 0;
}

void Mundo::hacerlesPecar(Persona* persona){
    persona->pecadosTotales = 0;
    for(int j = 0; j<7;j++){
        persona->pecados[j]+= QRandomGenerator::global()->bounded(1,100);
        persona->pecadosTotales+= persona->pecados[j];
    }
}

void Mundo::hacerBuenasAcciones(Persona* persona){
    persona->buenasAccionesTotales = 0;
    for(int j = 0; j<7;j++){
        persona->buenasAcciones[j]+= QRandomGenerator::global()->bounded(1,100);
        persona->buenasAccionesTotales+= persona->buenasAcciones[j];
    }
}

void Mundo::crearPoblacion(int cantSolicitada){
    //La mayor parte de las veces no sera la primera vez entonces preguntamos al inicio.
    for(int i = 0 ; i<cantSolicitada;i++){
        crearPersona();
    }

    if(generacion!=0){
        NodoDoble<Persona> * tmp = listaPersonasTotales->primerNodo;
        for(int i =0;i<listaPersonasTotales->largo;i++){
            asignarFamilia(tmp->dato);
            asignarAmigos(tmp->dato);
            tmp = tmp->siguiente;
        }
    }
    generacion++;
}

void Mundo::crearPersona(){
    Persona * nuevaPersona = new Persona();
    nuevaPersona->genero = "mujer";
    //Modificar para qe el genero sea aleatorio
    nuevaPersona->ID = QString::number(registroIds->generarId());
    nuevaPersona->pais = paises[QRandomGenerator::global()->bounded(0,99)];
    nuevaPersona->creencia = creencias[QRandomGenerator::global()->bounded(0,13)];
    nuevaPersona->apellido = apellidos[QRandomGenerator::global()->bounded(0,999)];
    nuevaPersona->profesion = profesiones[QRandomGenerator::global()->bounded(0,50)];
    if(nuevaPersona->genero == "mujer") nuevaPersona->nombre = nombresMujeres[QRandomGenerator::global()->bounded(0,499)];
    else nuevaPersona->nombre = nombresHombres[QRandomGenerator::global()->bounded(0,499)];

    nuevaPersona->fechaNacimiento = new FechaNacimiento();
    nuevaPersona->edad = longevidad->obtenerEdad(nuevaPersona);
    hacerBuenasAcciones(nuevaPersona);
    hacerlesPecar(nuevaPersona);

}
void Mundo::asignarFamilia(Persona* persona){
    int cantAmigos = QRandomGenerator::global()->bounded(0,51);
    NodoDoble<Persona> * tmp = listaPersonasTotales->primerNodo;
    //agregarMetodo de moverse x nodos en la lista para seleccionar gente random

    for(int i = 0 ;i<cantAmigos;i++){
        if(persona->pais  == tmp->dato->pais){
          tmp->dato->amigos->append(tmp->dato);
        }
    }

}
void Mundo::asignarAmigos(Persona* persona){
    int cantAmigos = QRandomGenerator::global()->bounded(0,51);
    NodoDoble<Persona> * tmp = listaPersonasTotales->primerNodo;
    //agregarMetodo de moverse x nodos en la lista para seleccionar gente random

    int cont = 0;
    while(cont<cantAmigos){
        if(persona->pais  == tmp->dato->pais){
          tmp->dato->amigos->append(tmp->dato);
          cont++;
        }
        else if(QRandomGenerator::global()->bounded(1,100) <40){
            tmp->dato->amigos->append(tmp->dato);
            cont++;
        }

        else {
            bool coinciden = false;
            Persona * tmp2 = tmp->dato->amigos->first();
            for(int i = 0;i<tmp->dato->amigos->length();i++){

                if(persona->amigos){

                    return;
                }
                tmp2-> //recorrer ambas listas de los amimgos de uno y los de esa persona
                        //y econtrar similitudes
            }
            if(coinciden)
            cont++;
        }
    }
}

void Mundo::thor(){

}
void Mundo::nebula(){

}
void Mundo::antMan(){

}
void Mundo::ironMan(){
    //Recorre el arbol, pregunta si ya pasó por ese nodo. Si no, hace random y depende del resultado salva ese nodo y lo pone true.
}            //Al terminar el proceso, restaura los valores de los nodos a false.
void Mundo::midnight(){

}
void Mundo::ebonyMaw(int IDCulpable){
    Persona * culpable = listaPersonasTotales->buscar(IDCulpable);  //modificar para que sea *

}
void Mundo::spiderMan(){

}
void Mundo::blackDwarf(){

}
void Mundo::corvusGlaive(){

}


