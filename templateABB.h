#ifndef TEMPLATEABB_H
#define TEMPLATEABB_H

//Estructura Nodo para el ABB
template <typename T> struct TreeNode{
    TreeNode<T> * izquierda;
    TreeNode<T> * derecha;
    T dato;
    TreeNode(){
        izquierda = derecha = nullptr;
        this->dato = nullptr;
    }
    TreeNode(T dato){
        izquierda = derecha = nullptr;
        this->dato = dato;
    }
};

//Template del ABB
template <typename T> struct Tree{
   TreeNode<T> * raiz;
    //Métodos Públicos

   //Métodos Privados
    void insertarNodo(TreeNode<T> *&ptrRaiz, TreeNode<T> *&nuevoNodo){
        if (ptrRaiz == nullptr) ptrRaiz = nuevoNodo;
        else if (nuevoNodo->dato < ptrRaiz->dato) insertarNodo(ptrRaiz->izquierda, nuevoNodo);
        else insertarNodo(ptrRaiz->derecha, nuevoNodo);
    }
};

#endif // TEMPLATEABB_H
