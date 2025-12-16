#ifndef HANDLEFILES_H
#define HANDLEFILES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

class handleFiles
{
public:
    handleFiles();
    static void generarArch();
    static FILE* abrirArchivo();
    static int byteSearch(FILE*);
};

#endif // HANDLEFILES_H
