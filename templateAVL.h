#include <QDebug>
#include "Persona.h"
#ifndef TEMPLATEAVL_H
#define TEMPLATEAVL_H
// C++ program to insert a node in AVL tree

// An AVL tree node
template<typename T> struct Nodo
{
    public:
    T * dato; //Persona
    Nodo *left;
    Nodo *right;
    int height;

    int feromonas;  //Para Ant Man
    bool utilizado; //true = ya pasó por ahi

    Nodo(T *dato){
        this->dato = dato;
        left = nullptr;
        right = nullptr;
        height = 1;
        feromonas = 0;
    }
};

template<typename T> struct AVL{
    Nodo<T> * root;
    int cantidadPersonas = 0;
    QList<Nodo<T>*> * listaArbol;
    QList<QString> * niveles;

public:

    void insertar(T * dato){
        root = insert(root, dato);
        cantidadPersonas++;
    }

    void imprimirArbol(){
        //verArbol(root, 0);
        qDebug() << "Altura: " + QString::number(root->height);
        qDebug() << "Cantidad: " + QString::number(this->cantidadPersonas);
        imprimirNiveles();
    }

     QList<Nodo<T>*> * aplastarArbol(){
       this->listaArbol = new QList<Nodo<T>*>();
       aplastarArbolPrivate(root);
       return listaArbol;
    }

     void imprimirNiveles(){
        niveles = new QList<QString>();
        for(int i=0; i<root->height; i++){
            niveles->append("Nivel "+QString::number(i)+": ");
        }
        imprimirNivelPrivate(root, 0);
        for(int i=0; i<niveles->size(); i++){
            qDebug().noquote() << niveles->at(i) + "\n";
        }
     }

     Nodo<T> * buscar(QString id){
        return buscarNodo(id, root);
     }

     bool estaEnElArbol(QString id){
         if(buscarNodo(id, root) == nullptr) return false;
         return true;
     }

     //Retorna una lista con todas las personas de un nivel solicitado.
     QList<Persona*>* buscarEnNivel(int nivel){
         if(nivel > root->height-1) return nullptr;
         QList<Persona*> * listaDelNivel = new QList<Persona*>();
         recorrerNivel(root, 0, listaDelNivel, nivel);
         return listaDelNivel;
     }

private:

     void imprimirNivelPrivate(Nodo<T> *nodo, int nivel){
         if(nodo!=nullptr){
            niveles->replace(nivel, niveles->at(nivel) +" "+nodo->dato->ID);
            imprimirNivelPrivate(nodo->left, nivel+1);
            imprimirNivelPrivate(nodo->right, nivel+1);
         }
     }

     void recorrerNivel(Nodo<T> * nodo, int nivelNodo, QList<Persona*> * lista, int nivelBuscado){
         if(nodo!= nullptr){
             if(nivelNodo == nivelBuscado) lista->append(nodo->dato);
             recorrerNivel(nodo->left, nivelNodo+1, lista, nivelBuscado);
             recorrerNivel(nodo->right, nivelNodo+1, lista, nivelBuscado);
         }
     }

     Nodo<T>* buscarNodo (QString valor, Nodo<T>* nodo)
     {
          if(nodo == nullptr)
            return nullptr;
          else if (nodo->dato->ID.toInt() == valor.toInt())
            return nodo;
          else if (nodo->dato->ID.toInt() < valor.toInt())
            return buscarNodo(valor, nodo->right);
          else
            return buscarNodo(valor, nodo->left);
      }

     void preOrder( Nodo<T>* node)
     {
         if (node == NULL)
             return;

         /* first print data of node */
          node->dato;

         /* then recur on left sutree */
         preOrder(node->left);

         /* now recur on right subtree */
         preOrder(node->right);
     }

    void * aplastarArbolPrivate(Nodo<T> *rootN)  //Genera una lista del arbol
    {
        if(rootN != nullptr)
        {
            listaArbol->append(rootN);
            aplastarArbolPrivate(rootN->left);
            aplastarArbolPrivate(rootN->right);
        }
    }

    void verArbol(Nodo<T> * nodo, int n)
    {
         if(nodo == nullptr)
              return;
         verArbol(nodo->right, n+1);

         for(int i=0; i<n; i++)
             qDebug()<<"   ";

         qDebug() << nodo->dato->ID <<endl;

         verArbol(nodo->left, n+1);
    }

    // A utility function to get maximum
    // of two integers
    int max(int a, int b)
    {
        return (a > b)? a : b;
    }

    // A utility function to get the
    // height of the tree
    int height(Nodo<T> *N)
    {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    /* Helper function that allocates a
    new Nodo<T> with the given dato and
    nullptr left and right pointers. */

    Nodo<T>* newNodo(T *dato)
    {
        Nodo<T> *nodo = new Nodo<T>(dato);
        return(nodo);
    }

    // A utility function to right
    // rotate subtree rooted with y
    // See the diagram given above.
    Nodo<T> *rightRotate(Nodo<T> *y)
    {
        Nodo<T> *x = y->left;
        Nodo<T> *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = max(height(y->left),
                        height(y->right)) + 1;
        x->height = max(height(x->left),
                        height(x->right)) + 1;

        // Return new root
        return x;
    }

    // A utility function to left
    // rotate subtree rooted with x
    // See the diagram given above.
    Nodo<T> *leftRotate(Nodo<T> *x)
    {
        Nodo<T> *y = x->right;
        Nodo<T> *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = max(height(x->left),
                        height(x->right)) + 1;
        y->height = max(height(y->left),
                        height(y->right)) + 1;

        // Return new root
        return y;
    }

    // Get Balance factor of Nodo<T> N
    int getBalance(Nodo<T> *N)
    {
        if (N == nullptr)
            return 0;
        return height(N->left) - height(N->right);
    }

    // Recursive function to insert a dato
    // in the subtree rooted with node and
    // returns the new root of the subtree.
    Nodo<T>* insert(Nodo<T>* node, T *dato)
    {
        // AGREGAR DATO->ID PERSONALIZARLO PARA PERSONAS.

        /* 1. Perform the normal BST insertion */
        if (node == nullptr)
            return(newNodo(dato));
        if (dato->ID.toInt() < node->dato->ID.toInt())
            node->left = insert(node->left, dato);
        else if (dato->ID.toInt() > node->dato->ID.toInt())
            node->right = insert(node->right, dato);
        else // Equal datos are not allowed in BST
            return node;

        /* 2. Update height of this ancestor node */
        node->height = 1 + max(height(node->left),
                            height(node->right));

        /* 3. Get the balance factor of this ancestor
            node to check whether this node became
            unbalanced */
        int balance = getBalance(node);

        // If this node becomes unbalanced, then
        // there are 4 cases

        // Left Left Case
        if (balance > 1 && dato->ID.toInt() < node->left->dato->ID.toInt())
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && dato->ID.toInt() > node->right->dato->ID.toInt())
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && dato->ID.toInt() > node->left->dato->ID.toInt())
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && dato->ID.toInt() < node->right->dato->ID.toInt())
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        /* return the (unchanged) node pointer */
        return node;
    }


};



#endif // TEMPLATEAVL_H
