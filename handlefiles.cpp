#include "handlefiles.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

handleFiles::handleFiles() {}

void handleFiles::generarArch()
{
    FILE *Fd;
    char car;
    char nomArch[100];

    string nombre;
    printf("Nombre del Archivo a GENERAR (sin extension): ");
    cin>>nombre;
    cin.get();   //ELIMINAR ENTER

    //PATH APP. QT
    // /Users/martinos/Documents/MATERIAS/AUTOMATAS\ I/MATERIAL/UNIDAD\ IV\ SINTACTICO/ANALIZADOR\ SINTACTICO\ REVISADO/appAnalizadorSintactico_

    //PATH APP. XCODE
    //sprintf(nomArch,"/Users/martinos/Desktop/appASintactico_XCode/%s.dat",nombre.c_str());  //,'\0');


    sprintf(nomArch,"%s.dat",nombre.c_str());
    Fd = fopen(nomArch,"w+b");

    if(Fd == nullptr)
    {
        cout<<"NO SE PUEDE ABRIR EL ARCHIVO : "<<nomArch;
        exit(-1);
    }
    printf("teclea el archivo (<@> para terminar el archivo): \n");



    //LA INFO ESTA EN EL BUFFER
    do
    {          //CHECAR
        car = cin.get();

        // if( car == '\n')  //13)
        // {
        //     car = '\n';
        //     printf("\n");
        // }

        if(car != 64 && car != 8)
            fwrite(&car,sizeof(car),1,Fd);

    }while(car != 64);

    fclose(Fd);
}

FILE* handleFiles::abrirArchivo()
{
    FILE* Fd;
    char nomArch[100];
    char *nombre = new char[100];

    printf("\n\n Nombre del Archivo a ABRIR(sin extension): ");
    //gets(nombre);
    //cin>>nombre;
    cin.get();  //ELIMINAR EL ENTER
    cin.getline(nombre,100,'\n');

    //sprintf(nomArch,"/Users/martinos/Desktop/appASintactico_XCode/%s.dat",nombre);  //,'\0');
    sprintf(nomArch,"%s.dat",nombre);


    Fd = fopen(nomArch,"r+b");

    if(Fd==NULL)
    {
        printf("NO SE PUEDE ABRIR EL ARCHIVO");
        exit(-1);    //cin.get();

    }
    else
    {
        printf("EL ARCHIVO SE ENCUENTRA ABIERTO \n");
    }

    return Fd;
}

int handleFiles::byteSearch(FILE *Fd)
{
    int aux;
    fseek(Fd,0L,SEEK_END);
    aux = (int) ftell(Fd);
    fseek(Fd,0L,SEEK_SET);
    return aux;
}




