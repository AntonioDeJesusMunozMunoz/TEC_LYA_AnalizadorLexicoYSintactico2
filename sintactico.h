#ifndef SINTACTICO_H
#define SINTACTICO_H

#define MAX 50
#include <string.h>
#include <iostream>
#include <vector>


using std::vector;
using namespace std;

class sintactico
{
private:
    static const int NUM_NT = 21;
    static const int NUM_TOK = 24;

    enum Token {
        TOK_ID = 0,
        TOK_MAS,
        TOK_MENOS,
        TOK_IGUAL,
        TOK_ASTERISCO,
        TOK_DIVISION,  //5
        TOK_PUNTOYCOMA,
        TOK_PARENTESISIZQ,
        TOK_PARENTESISDER,
        TOK_CORCHETEIZQ,
        TOK_CORCHETEDER,   //10
        TOK_LLAVEIZQ,
        TOK_LLAVEDER,
        TOK_COMA,
        TOK_NUM,
        TOK_REAL, //15
        TOK_CHAR,
        TOK_INT,
        TOK_FLOAT,
        TOK_PUTS,
        TOK_CTE_LIT, //20
        TOK_$,
        TOK_e,
        TOK_REFFERENCE
    };

    enum NoTerminal {
        NT_D = 0,
        NT_L,
        NT_LP,
        NT_I,
        NT_IP,
        NT_A,  //5
        NT_AP,
        NT_K,
        NT_T,
        NT_TP,
        NT_TPP,  //10
        NT_AR,
        NT_Dp,
        NT_Ep,
        NT_F,
        NT_E,   //15
        NT_P
    };

    enum TipoSimbolo {
        TERMINAL,
        NO_TERMINAL
    };

    struct Simbolo {
        TipoSimbolo tipo;
        int valor;   // TOK_* o NT_*
    };

    struct Produccion {
        vector<Simbolo> cuerpo;  // vacío = ε
    };




    char (*tokens)[100];
    int cima = -1;
    //char pilac[MAX][10];
    vector<Simbolo> pila;

    char token[24][10] = {
        "Id",        // TOK_ID = 0
        "+",         // TOK_MAS
        "-",         // TOK_MENOS
        "=",         // TOK_IGUAL
        "*",         // TOK_ASTERISCO
        "/",         // TOK_DIVISION
        ";",         // TOK_PUNTOYCOMA
        "(",         // TOK_PARENTESISIZQ
        ")",         // TOK_PARENTESISDER
        "[",         // TOK_CORCHETEIZQ
        "]",         // TOK_CORCHETEDER
        "{",         // TOK_LLAVEIZQ
        "}",         // TOK_LLAVEDER
        ",",         // TOK_COMA
        "Num",       // TOK_NUM
        "Real",      // TOK_REAL
        "char",      // TOK_CHAR
        "int",       // TOK_INT
        "float",     // TOK_FLOAT
        "puts",      // TOK_PUTS
        "Cte.Lit",   // TOK_CTE_LIT
        "$",         // TOK_$
        "",          // TOK_e
        "&"          // TOK_REFFERENCE
    };

    char varsint[21][5] = {
        "D",    // NT_D = 0
        "L",    // NT_L
        "L'",   // NT_LP
        "I",    // NT_I
        "I'",   // NT_IP
        "A",    // NT_A
        "A'",   // NT_AP
        "K",    // NT_K
        "T",    // NT_T
        "T'",   // NT_TP
        "T''",  // NT_TPP
        "Ar",   // NT_AR
        "Dp",   // NT_Dp
        "Ep",   // NT_Ep
        "F",    // NT_F
        "E",    // NT_E
        "P"     // NT_P
    };

    Produccion tablaM[NUM_NT][NUM_TOK];


public:
    sintactico(char (*tokens)[100]);
    void cargarProducciones();
    void vanalisis_sintactico();
    void insertapila(string elem);
    void eliminapila();
    int estoken(char x[]);
};

#endif // SINTACTICO_H
