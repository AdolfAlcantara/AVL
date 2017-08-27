//
// Created by Chronos-Laptop on 24/8/2017.
//

#ifndef AVL_ARBOL_H
#define AVL_ARBOL_H
#include "nodo.h"
#include "datafile.h"
class arbol
{
public:
    arbol(datafile*arch, datafile*ind);
    int Insertar(nodo **raiz,nodo*);
    nodo* Buscar(int value);

    void RS_Der(nodo **sraiz);
    void RS_Izq(nodo **sraiz);
    void RD_Der(nodo **sraiz);
    void RD_Izq(nodo **sraiz);
    void Balanceo(nodo **sraiz);
    void recorridoPreorden(nodo *raiz);
    int calcularAlturas(nodo *raiz);

    std::vector<nodo> Escribir();
    std::vector<nodo> Leer();

    virtual ~arbol();

    nodo*raiz;
    int cantNodos;
    datafile*archivo,*indice;


};


#endif //AVL_ARBOL_H
