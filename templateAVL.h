#include <QDebug>
#ifndef TEMPLATEAVL_H
#define TEMPLATEAVL_H
// C++ program to insert a node in AVL tree

// An AVL tree node
template<typename T> struct Nodo
{
    public:
    T dato;
    Nodo *left;
    Nodo *right;
    int height;

    Nodo(T dato){
        this->dato = dato;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};


template<typename T> struct AVL{
    Nodo<T> * root;

public:

    Nodo<T>* insertar(T dato){
        return insert(root, dato);
    }

    void preOrder()
    {
        if(root != nullptr)
        {
            qDebug() << root->dato << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }
private:

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

    Nodo<T>* newNodo(T dato)
    {
        Nodo<T> *nodo = new Nodo<T>();
        nodo->dato = dato;
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
    Nodo<T>* insert(Nodo<T>* node, T dato)
    {
        /* 1. Perform the normal BST insertion */
        if (node == nullptr)
            return(newNodo(dato));
        if (dato < node->dato)
            node->left = insert(node->left, dato);
        else if (dato > node->dato)
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
        if (balance > 1 && dato < node->left->dato)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && dato > node->right->dato)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && dato > node->left->dato)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && dato < node->right->dato)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        /* return the (unchanged) node pointer */
        return node;
    }


};



#endif // TEMPLATEAVL_H