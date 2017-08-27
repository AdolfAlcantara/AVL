//
// Created by Chronos-Laptop on 24/8/2017.
//

#include <windef.h>
#include <vector>
#include <iostream>
#include "arbol.h"
arbol::arbol(datafile*arch, datafile *ind)
{
    raiz=0;
    cantNodos=0;
    archivo=arch;
    indice = ind;
}

int max(int x, int y){
    if(x>y){
        return x;
    }
    return y;
}

int arbol::Insertar(nodo **sraiz, nodo *n)
{

    if(*sraiz==0){
        *sraiz = n;
        cantNodos++;
        return 0;
    }
    nodo *sr = *sraiz;
    if(sr->valor > n->valor ){
        int h = Insertar(&(sr->izq),n);
        sr->AIzq = h+1;
    }else{
        int h = Insertar(&(sr->der),n);
        sr->ADer = h+1;
    }
    Balanceo(sraiz);
    calcularAlturas(raiz);
    return max(sr->AIzq,sr->ADer);
}

nodo *arbol::Buscar(int value)
{
    char*data = indice->LeerTodo();
    int cantNodos=0;
    int posiciondato=0;
    memcpy(&cantNodos,&data[0],4);
    int pos=4;
    for(int i=0;i<cantNodos;i++){
        int valor=0;;
        memcpy(&valor,&data[pos],4);
        if(valor == value){
            pos+=4;
            memcpy(&posiciondato,&data[pos],4);
            break;
        }
        pos+=8;
    }

    char*data2 = archivo->Leer(posiciondato,16);
    int pos2=0;
    nodo *buscado = new nodo();
    memcpy(&buscado->valor,&data2[pos2],4);
    pos2+=4;
    memcpy(&buscado->NRR,&data2[pos2],4);
    pos2+=4;
    memcpy(&buscado->AIzq,&data2[pos2],4);
    pos2+=4;
    memcpy(&buscado->ADer,&data2[pos2],4);
    pos+=4;

    return buscado;

}

void arbol::Balanceo(nodo **sraiz)
{
    nodo*sr = *sraiz;
    int alturaIzq = sr->AIzq;
    int alturaDer = sr->ADer;
    if(alturaIzq-alturaDer==2){
        nodo*__HI = sr->izq;
        if(__HI->AIzq>=__HI->ADer){
            RS_Der(sraiz);
        }else{
            RD_Der(sraiz);
        }
    }else if(alturaIzq-alturaDer==-2){
        nodo*__HD = sr->der;
        if(__HD->AIzq<=__HD->ADer){
            RS_Izq(sraiz);
        }else{
            RD_Izq(sraiz);
        }
    }
}

void arbol::RS_Der(nodo **sraiz)
{
    nodo*sr = *sraiz;
    nodo *__HI = sr->izq;
    sr->izq = __HI->der;
    __HI->der = sr;
    *sraiz = __HI;
}
void arbol::RS_Izq(nodo **sraiz)
{
    nodo*sr = *sraiz;
    nodo*__HD = sr->der;
    sr->der = __HD->izq;
    __HD->izq = sr;
    *sraiz = __HD;
}
void arbol::RD_Der(nodo **sraiz)
{
    nodo *sr = *sraiz;
    RS_Izq(&(sr->izq));
    RS_Der(sraiz);

}
void arbol::RD_Izq(nodo **sraiz)
{
    nodo *sr = *sraiz;
    RS_Der(&(sr->der));
    RS_Izq(sraiz);
}

std::vector<nodo> arbol::Escribir()
{
    std::vector<nodo>nodos;
    int posicion = 4;
    nodos.push_back(*raiz);
    nodos[0].NRR=posicion;
    for(int i=0;i<cantNodos;i++){
//        int pos=1;
        nodo temp = nodos[i];
        if(temp.izq!=0){
            posicion+=16;
            temp.izq->NRR=posicion;
            nodos.push_back(*temp.izq);
        }
        if(temp.der!=0){
            posicion+=16;
            temp.der->NRR=posicion;
            nodos.push_back(*temp.der);
        }
    }

    int tamanototal = 4+cantNodos*16;//archivo
    int tamanototal2= 4+cantNodos*8;//indice
    char*data = new char[tamanototal];//archivo
    char*data2 = new char[tamanototal2];//indice
    int pos=0,pos2=0;//pos es de archivo, pos2 es de indice
    /*------------archivo-------------*/
    memcpy(&data[pos],&cantNodos,4);
    pos+=4;
    /*---------------indice-----------*/
    memcpy(&data2[pos2],&cantNodos,4);
    pos2+=4;
    for(int i=0;i<nodos.size();i++){
        nodo temp = nodos[i];
        /*--------archivo-------*/
        memcpy(&data[pos],&temp.valor,4);
        pos+=4;
        memcpy(&data[pos],&temp.NRR,4);
        pos+=4;
        memcpy(&data[pos],&temp.AIzq,4);
        pos+=4;
        memcpy(&data[pos],&temp.ADer,4);
        pos+=4;
        /*-------indice--------*/
        memcpy(&data2[pos2],&temp.valor,4);
        pos2+=4;
        memcpy(&data2[pos2],&temp.NRR,4);
        pos2+=4;
    }

    archivo->Escribir(data,tamanototal);
    indice->Escribir(data2,tamanototal2);
    return nodos;
}

std::vector<nodo> arbol::Leer()
{

    std::vector<nodo> nodos;
    char*data = archivo->LeerTodo();
    memcpy(&cantNodos,&data[0],4);
    for(int i=0;i<cantNodos;i++){
        int pos = i*16+4;
        nodo* nnodo = new nodo();
        memcpy(&nnodo->valor,&data[pos],4);
        pos+=4;
        memcpy(&nnodo->NRR,&data[pos],4);
        pos+=4;
        memcpy(&nnodo->AIzq,&data[pos],4);
        pos+=4;
        memcpy(&nnodo->ADer,&data[pos],4);

        nodos.push_back(*nnodo);
    }

    raiz = &nodos[0];
    for(int i=0;i<cantNodos;i++){
        if(nodos[i].AIzq!=0){
            nodos[i].izq = &nodos[2*i+1];
        }
        if(nodos[i].ADer!=0){
            nodos[i].der = &nodos[2*i+2];
        }
    }

    return nodos;
}

void arbol::recorridoPreorden(nodo*t)
{
    std::cout<<t->valor<<',';
    if(t->izq!=0){
        recorridoPreorden(t->izq);
    }
    if(t->der!=0){
        recorridoPreorden(t->der);
    }
}

int arbol::calcularAlturas(nodo *raiz)
{
    if(raiz==0){
        return 0;
    }
    int hi = calcularAlturas(raiz->izq);
    raiz->AIzq = hi;
    int hd=calcularAlturas(raiz->der);
    raiz->ADer = hd;
    return max(hi,hd)+1;
}

arbol::~arbol()
{

}
