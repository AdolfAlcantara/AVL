//
// Created by Chronos-Laptop on 24/8/2017.
//

#ifndef AVL_NODO_H
#define AVL_NODO_H


class nodo
{
public:
    nodo();
    nodo(int n);
    virtual ~nodo();

    int valor;
    int AIzq;
    int ADer;
    int NRR;
    nodo*der;
    nodo*izq;

};


#endif //AVL_NODO_H
