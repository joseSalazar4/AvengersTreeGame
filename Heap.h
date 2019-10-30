#ifndef HEAP_H
#define HEAP_H
#include <QList>
#include "Persona.h"
#include "QDebug"

struct Heap{
    QList<Persona*> * heap;
    int index;
public:
    Heap(){
        index = 0;
        this->heap = new QList<Persona*>;
    }

    //Usar este metodo en los heaps de pecados
    //La prioridad lo tienen las personas con mayor cantidad de pecados
    void insertarPrioridadMax(Persona*p){
        //if(p->ID< 0) return;
        heap->insert(index, p);
        algoritmoInsertarPrioridadMax(index);
        index++;
    }

    //Usar este metodo en los heaps de buenas acciones
    //La prioridad son las personas con menos cantidaad de buenas acciones
    void insertarPrioridadMin(Persona*p){
        //if(p->ID< 0) return;
        heap->insert(index, p);
        algoritmoInsertarPrioridadMin(index);
        index++;
    }

    Persona* eliminarPrioridadMax(){
        Persona* ultimoElemento = heap->at(index-1);
        Persona* eliminado = heap->at(0);
        heap->replace(0, ultimoElemento);
        index--;
        algoritmoEliminarPrioridadMax(index, 0);
        return eliminado;
    }

    Persona* eliminarPrioridadMin(){
        Persona* ultimoElemento = heap->at(index-1);
        Persona* eliminado = heap->at(0);
        heap->replace(0, ultimoElemento);
        index--;
        algoritmoEliminarPrioridadMin(index, 0);
        return eliminado;
    }

    void imprimirPecadosTotales(){
        for(int i=0; i<heap->size(); i++){
            qDebug() << (heap->at(i)->pecadosTotales);
        }
    }

    void imprimirBuenasAccionesTotales(){
        for(int i=0; i<heap->size(); i++){
            qDebug() << (heap->at(i)->buenasAccionesTotales);
        }
    }

private:
    void algoritmoEliminarPrioridadMax(int n, int i){
        int largest = i; // Initialize largest as root
        int l = 2 * i + 1; // left = 2*i + 1
        int r = 2 * i + 2; // right = 2*i + 2

        // If left child is larger than root
        if (l < n && heap->at(l)->pecadosTotales > heap->at(largest)->pecadosTotales)
            largest = l;

        // If right child is larger than largest so far
        if (r < n && heap->at(r)->pecadosTotales > heap->at(largest)->pecadosTotales)
            largest = r;

        // If largest is not root
        if (largest != i) {
            heap->swapItemsAt(i, largest);

            // Recursively heapify the affected sub-tree
            algoritmoEliminarPrioridadMax(n, largest);
        }
    }

    void algoritmoEliminarPrioridadMin(int n, int i){
        int lowest = i; // Initialize largest as root
        int l = 2 * i + 1; // left = 2*i + 1
        int r = 2 * i + 2; // right = 2*i + 2

        // If left child is lower than root
        if (l < n && heap->at(l)->buenasAccionesTotales < heap->at(lowest)->buenasAccionesTotales)
            lowest = l;

        // If right child is lower than largest so far
        if (r < n && heap->at(r)->buenasAccionesTotales < heap->at(lowest)->buenasAccionesTotales)
            lowest = r;

        // If lowest is not root
        if (lowest != i) {
            heap->swapItemsAt(i, lowest);

            algoritmoEliminarPrioridadMin(n, lowest);
        }
    }

    void algoritmoInsertarPrioridadMax(int i){
        int parent = (i - 1) / 2;
        if(i==0) parent = 0;
        if (parent > 0) {
            if (heap->at(i)->pecadosTotales > heap->at(parent)->pecadosTotales) {
                heap->swapItemsAt(i, parent);
                algoritmoInsertarPrioridadMax(parent);
          }
       }
    }

    void algoritmoInsertarPrioridadMin(int i){
        int parent = (i - 1) / 2;
        if(i==0) parent = 0;
        if (parent > 0) {
            if (heap->at(i)->buenasAccionesTotales < heap->at(parent)->buenasAccionesTotales) {
                heap->swapItemsAt(i, parent);
                algoritmoInsertarPrioridadMin(parent);
          }
       }
    }

};

#endif // HEAP_H
