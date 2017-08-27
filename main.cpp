#include <iostream>
#include <vector>
#include "arbol.h"

using namespace std;

int main()
{

    datafile *archivo  = new datafile("../nuevo");
    datafile *indice = new datafile("../indice");
  arbol *arb = new arbol(archivo,indice);

//
    arb->Insertar(&arb->raiz,new nodo(50));
    arb->Insertar(&arb->raiz,new nodo(49));
    arb->Insertar(&arb->raiz,new nodo(51));
    arb->Insertar(&arb->raiz,new nodo(30));
    arb->Insertar(&arb->raiz,new nodo(45));
//
    cout<<arb->raiz->valor<<endl;
    cout<<arb->raiz->izq->valor<<endl;
    cout<<arb->raiz->der->valor<<endl;
    cout<<arb->cantNodos<<endl;

    cout<<"--------"<<endl;
    arb->recorridoPreorden(arb->raiz);
    cout<<""<<endl;
        cout<<"----------"<<endl;
//
    std::vector<nodo>nodos = arb->Escribir(); //<-----pone los datos en un vector y ademas los escribe
//
    for(int i=0;i<arb->cantNodos;i++){
        cout<<nodos[i].valor<<endl;
        cout<<nodos[i].NRR<<endl;
        cout<<nodos[i].izq<<endl;
        cout<<nodos[i].der<<endl;
        cout<<nodos[i].AIzq<<endl;
        cout<<nodos[i].ADer<<endl;
        cout<<"--------"<<endl;
    }
//

//
//    nodo*n = arb->Buscar(51);
//    cout<<n->NRR<<endl;
//
//    std::vector<nodo>nodos=arb->Leer();   //<----lee los datos y los pone en un vector para organizar el arbol de nuevo
//
//    for(int i=0;i<arb->cantNodos;i++){
//        cout<<nodos[i].valor<<endl;
//        cout<<nodos[i].NRR<<endl;
//        cout<<nodos[i].izq<<endl;
//        cout<<nodos[i].der<<endl;
//        cout<<nodos[i].AIzq<<endl;
//        cout<<nodos[i].ADer<<endl;
//        cout<<"--------"<<endl;
//    }
//
//    arb->recorridoPreorden(arb->raiz);

}