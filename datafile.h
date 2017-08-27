//
// Created by Chronos-Laptop on 25/8/2017.
//

#ifndef DATAFILE_H
#define DATAFILE_H
#include <stdio.h>


class datafile
{
public:
    datafile(char *path);
    void Abrir();
    void Cerrar();
    void Escribir(char*data, int longitud);
    char * Leer(int pos, int longitud);
    char * LeerTodo();
    bool isEmpty();
    virtual ~datafile();

    // protected:

    //   private:
    char *path;
    FILE *archivo;
};

#endif // DATAFILE_H
