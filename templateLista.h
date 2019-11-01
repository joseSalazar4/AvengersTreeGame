#ifndef TEMPLATELISTA_H
#define TEMPLATELISTA_H
#include <QString>
#include <QDebug>

//Template de Lista doblemente enlasada

template <typename T> struct NodoDoble{
    NodoDoble<T> * siguiente;
    NodoDoble<T> * anterior;
    T * dato;
    NodoDoble(){
        siguiente = nullptr;
        anterior = nullptr;
        this->dato = nullptr;
    }

    NodoDoble(T * dato){
        siguiente = nullptr;
        anterior = nullptr;
        this->dato = dato;
    }
};

template <typename T> struct ListaDoble{
    NodoDoble<T> * primerNodo;
    NodoDoble<T> * ultimoNodo;
    int largo;


    ListaDoble(){
        primerNodo = ultimoNodo = nullptr;
        largo = 0;
    }

    void insertar(T * dato){
        if(estaVacio()){
            primerNodo = ultimoNodo = new NodoDoble<T>(dato);
            largo++;
        }
        else{
            primerNodo->anterior = new NodoDoble<T>(dato);
            primerNodo->anterior->siguiente = primerNodo;
            primerNodo = primerNodo->anterior;
            largo++;
        }
    }

    bool estaVacio(){
        return primerNodo == nullptr;
    }


    bool estaEnLista(int ID){
        if(!estaVacio()){
            NodoDoble<T> * temp = primerNodo;
            while(temp != nullptr){
                if(temp->dato->ID == ID)
                    return true;
                temp = temp->siguiente;
            }
        }
        return false;
    }

   T * buscar(int ID){
    //Devuelve el nodo solicitado
    if(!estaVacio()){
        NodoDoble<T> * temp = primerNodo;
        while(temp != nullptr){
            if(temp->dato->ID == ID)
                return temp->dato;
            temp = temp->siguiente;
            }
        }
    return nullptr;
    }

   NodoDoble<T> * buscarNodo(QString ID){
    //Devuelve el nodo solicitado
    if(!estaVacio()){
        NodoDoble<T> * temp = primerNodo;
        while(temp != nullptr){
            if(temp->dato->ID == ID)
                return temp;
            temp = temp->siguiente;
            }
        }
    return nullptr;
    }

   T * buscarNombre(QString nombre){
    //Devuelve el nodo solicitado
    if(!estaVacio()){
        NodoDoble<T> * temp = primerNodo;
        while(temp != nullptr){
            if(temp->dato->nombre == nombre)
                return temp->dato;
            temp = temp->siguiente;
            }
        }
    return nullptr;
    }

   void imprimir(){
       NodoDoble<T> * temp = primerNodo;
       while(temp!=nullptr){
           qDebug() << temp->dato->imprimir();
           temp = temp->siguiente;
       }
   }

   T* at(int index){
       if(estaVacio() || index >= largo || index < 0){
           qDebug() << "index out of bounds" <<endl;
       }
       else{
           NodoDoble<T> * temp = primerNodo;
           while(index != 0){
               temp = temp->siguiente;
               index--;
           }
           return temp->dato;
       }
   }

   NodoDoble<T> * atNodo(int index){
       if(estaVacio() || index >= largo || index < 0){
           qDebug() << "index out of bounds" <<endl;
       }
       else{
           NodoDoble<T> * temp = primerNodo;
           while(index != 0){
               temp = temp->siguiente;
               index--;
           }
           return temp;
       }
   }



};
#endif // TEMPLATELISTA_H
