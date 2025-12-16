
//
//  main.cpp
//  appASintactico_XCode
//
//  Created by Martin Valdes
//  Copyright ©  Martin Valdes. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <handlefiles.h>
#include <lexico.h>
#include <sintactico.h>


#include <iostream>
using namespace std;


// PROYECTO FINAL
// REVISIÓN PREVIA: ?
// REDISEÑAR ESTA APP. APLICANDO POO,
// PRINCIPALMENTE CUANDO QUEDE CLARO EL FUNCIONAMIENTO

//  CLASES:  LEXICO, SINTACTICO, PILA, TABLA DE SIMBOLOS, ARCHIVOS.

//REQUERIMIENTOS:
//  DOCUMENTAR LA APP.
//  USAR UNA TABLA DE EXCEL PARA MOSTRAR LA TABLA M
//  ELABORAR UNA PRESENTACIÓN EN POWER POINT
//  DÍA DE LA EXPOSICIÓN: MIERCOLES 10 JUNIO.

// SE REQUIERE CORREGIR Y EXPLICAR LA TABLA M DE ESTA APP.,
// EL ANÁLISIS Y LA IMPLEMENTACIÓN DE LA GRAMATICA QUE INCLUYE:
// LA DECLARACIÓN, LA ASIGNACIÓN
// Y LAS OPERACIONES ARITMÉTICAS

#define MAXTOKEN 100
#define NUMPALRES 4
#define MAX 50




int buscaTabla(char a[], char x[]);
int estoken(char x[]);

bool finarch = false;
FILE *Fd;


// AGREGAR EL RECONOCIMIENTO DE NUMEROS REALES
// ERROR EN ESTA APP. NO VALIDA NUMEROS FLOTANTES O REALES
int main(void)
{
    char resp;
    do
    {
        /*CREACIÓN DEL ARCHIVO*/
        puts("Desea Generar el Archivo (s/n) : ");
        resp = cin.get();

        //GENERAR ARCHIVO O ABRIR ARCHIVO
        if(strchr("Ss",resp))
            handleFiles::generarArch();

        Fd = handleFiles::abrirArchivo();



        //NUMERO DE BYTES DEL ARCHIVO
        int numBytesArch = handleFiles::byteSearch(Fd);

        lexico lex(Fd, numBytesArch);
        char (*tokens)[100] = lex.getTokens();
        sintactico parser(tokens);


        if(numBytesArch==0)
        {
            printf("El archivo NO Tiene Datos. Pulse una tecla");
            if(cin.get() == 0) //  getch()==0)
            { cin.get();//getch();
                exit(-1);
            }
        }
        else{
            //ANALIZA LÉXICO
            lex.vanalisislexico();
        }
        fclose(Fd);


        printf("Salida del Analizador Lexico (asTokens)");
        lex.vmuestra();



        printf("Pulse una tecla para continuar");
        if(cin.get() == 0) //getch()==0)
            cin.get();     //getch();
        parser.vanalisis_sintactico();
        cin.get();


        printf("Presiona (sS) para continuar ? : " );
        cin>>resp;
        cin.get();

    }while (strchr("Ss",resp));

    return 0;
}









