#ifndef LEXICO_H
#define LEXICO_H

#define MAXTOKEN 100
#define NUMPALRES 4
#define MAX 50

#include <stdlib.h>
#include <stdio.h>

class lexico
{
private:
    FILE* Fd;
    char sLexema[127];
    char sLinea[127];
    char non[6]="13579", par[6]="24680";
    char asTokens [MAXTOKEN][100];

    int indice=0;
    int edoAct, edoIni, iniToken=0;
    int k;
    int numBytesArch;

    char PalRes[5][10]= {"char", "float","int","puts"}; //printf
public:
    lexico(FILE*, int);
    void vanalisislexico();
    void viniedos();
    char nextchar();
    void vretract();
    int edoActesacept();
    void falla();
    void recuperaerror();
    int esId();
    void vmuestra();
    char (*getTokens())[100];
};

#endif // LEXICO_H
