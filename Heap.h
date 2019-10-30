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

    void insertar(Persona*p){
        if(p->pecadosTotales<0) return;
        heap->insert(index, p);
        algoritmoInsertar(index);
        index++;
    }

    void eliminar(){
        Persona* ultimoElemento = heap->at(index-1);
        heap->replace(0, ultimoElemento);
        index--;
        algoritmoEliminar(index, 0);
    }

    void imprimir(){
        for(int i=0; i<heap->size(); i++){
            qDebug() << QString::number(heap->at(i)->pecadosTotales);
        }
    }
private:
    void algoritmoEliminar(int n, int i){
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
            algoritmoEliminar(n, largest);
        }
    }

    void algoritmoInsertar(int i){
        // Find parent

        int parent = (i - 1) / 2;
        if(i==0) parent = 0;
        if (parent > 0) {
            // For Max-Heap
            // If current node is greater than its parent
            // Swap both of them and call heapify again
            // for the parent
            if (heap->at(i)->pecadosTotales > heap->at(parent)->pecadosTotales) {
               heap->swapItemsAt(i, parent);

                // Recursively heapify the parent node
                algoritmoInsertar(parent);
          }
       }
    }



};

#endif // HEAP_H
