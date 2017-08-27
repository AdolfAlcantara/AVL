//
// Created by Chronos-Laptop on 25/8/2017.
//

#include "datafile.h"
#include <iostream>
datafile::datafile(char *path)
{
    this->path = path;
    //archivo=0;
}

void datafile::Abrir()
{
    //std::cout<<"se abrio"<<std::endl;
    archivo  = fopen(path, "rb+");
}

void datafile::Cerrar()
{
    //std::cout<<"se cerro"<<std::endl;
    fclose(archivo);
}

/* pos es el bloque donde se va a escribir*/
void datafile::Escribir(char* data, int longitud)
{
    Abrir();
    if(fseek(archivo,0,SEEK_SET)==0){
        fwrite(data,sizeof(char),longitud,archivo);
    }
    Cerrar();
}

char* datafile::Leer(int pos, int longitud)
{
    Abrir();
    char  *buffer = new char[longitud];
    if(fseek(archivo,pos,SEEK_SET)==0){
        fread(buffer, sizeof(char),longitud,archivo);
    }
    Cerrar();
    return buffer;

}

char* datafile::LeerTodo()
{
    Abrir();
    fseek(archivo,0,SEEK_END);
    int tam = ftell(archivo);
    fseek(archivo,0,SEEK_SET);
    char*buffer = new char[tam];
    fread(buffer,sizeof(char),tam,archivo);
    Cerrar();
    return buffer;
}

bool datafile::isEmpty()
{

    if(fseek(archivo,0,SEEK_END)==0){
        return (ftell(archivo)<=0);
    }
    return true;
}

datafile::~datafile()
{
    //dtor
}
