#include "mundo.h"

//Agregar metodo para enviar correos

Mundo::Mundo()
{
    listaPersonasTotales = new ListaDoble<Persona>();
    arbolMundo = new AVL<Persona>();
    generacion = 0;
}
