#ifndef SINTACTICO_H
#define SINTACTICO_H

#define MAX 50
#include <string.h>
#include <iostream>

using namespace std;

class sintactico
{
private:
    enum Token {
        TOK_X = 0,          // "x" (dummy)
        TOK_PUNTOYCOMA,     // ";"
        TOK_COMA,           // ","
        TOK_ASTERISCO,      // "*"
        TOK_ID,             // "Id"
        TOK_CORCHETE_ABRE,  // "["
        TOK_CORCHETE_CIERRA,// "]"
        TOK_NUM,            // "Num"
        TOK_CHAR,           // "char"
        TOK_INT,            // "int"
        TOK_FLOAT,          // "float"
        TOK_PUTS,           // "puts"
        TOK_PAR_ABRE,       // "("
        TOK_PAR_CIERRA,     // ")"
        TOK_CTE_LIT,        // "Cte.Lit"
        TOK_LLAVE_ABRE,     // "{"
        TOK_LLAVE_CIERRA,   // "}"
        TOK_ASIGNACION,     // "="
        TOK_MAS,            // "+"
        TOK_MENOS,          // "-"
        TOK_DIV,            // "/"
        TOK_REAL            // "Real"
    };

    enum NoTerminal {
        NT_X = 0,
        NT_D,
        NT_L,
        NT_LP,
        NT_I,
        NT_IP,
        NT_A,
        NT_AP,
        NT_K,
        NT_T,
        NT_F,
        NT_E,
        NT_P
    };

    enum ParserConst {
        VACIO = 999
    };

    char (*tokens)[100];
    int cima = -1;
    char pilac[MAX][10];

    char token[22][8] = {"x", ";", ",", "*", "Id", "[", "]", "Num", "char", "int", "float",
                         "puts", "(", ")", "Cte.Lit", "{", "}", "=","+","-","/", "Real"};

    char varsint[15][3]={"x", "D", "L", "L'", "I", "I'", "A", "A'", "K",
                           "T", "F", "E", "P"};

    // e -> cadena vacia
    int tablaM[100][8]= {
        {1, 5, 1, 5, 999, -1, 999, 999},           //    [       D->I';
        {1, 5, 1, 5, 999, -1, 999, 999},           //    ;       D->I';
        {1, 1, 1, 5, 999, -1, 999, 999},           //    id      D->PL';
        {1, 7, 1, 5, 3, -1, 999, 999},             //    num     D->I'L';
        {1, 8, 1, 9, 2, -1, 999, 999},             //    char    D->TL;
        {1, 9, 1, 9, 2, -1, 999, 999},             //    int     D->TL;
        {1, 10, 1, 9, 2, -1, 999, 999},            //    float   D->TL;

        /* 5 */   {2, 3, 2, 4, 3, 999, 999, 999},  //    *       L->IL'
        {2, 4, 2, 4, 3, 999, 999, 999},            //    Id      L->IL'
        {3, 1, 3, 5, 999, 999, 999, 999},          //    ;       L'->I'
        {3, 1, 3, 999, 999, 999, 999, 999},        //    ;       L'->e
        {3, 2, 3, -2, 4, 3, 999, 999},             //    ,       L'->,IL'

        /* 10 */   {3, 3, 3, -3, 8, 3, 999, 999},  //    *       L'->*KL'
        {3, 18, 3, 12, 3, 999, 999, 999},          //    +       L'->PL'
        {3, 19, 3, 12, 3, 999, 999, 999},          //    -       L'->PL'
        {3, 20, 3, 12, 3, 999, 999, 999},          //    /       L'->PL'
        {3, 14, 3, -14, 5, 999, 999, 999},         // cte.Lit.   L'->cte Lit. I'
        {4, 3, 4, -3, -4, 5, 999, 999},            //    *       I->*Id I'
        {4, 4, 4, -4, 5, 999, 999, 999},           //    Id      I->Id I'
        {5, 1, 5, 999, 999, 999, 999, 999},        //    ;       I'->e

        /* 15 */       {5, 2, 5, 999, 999, 999, 999, 999},// , I'->e
        {5, 5, 5, 6, 999, 999, 999, 999}, // [ I' -> A
        //{5, 7, 5, -7, 999, 999, 999, 999}, //Num I' -> Num
        //{5, 12, 5, 7, 8, 11, 999, 999}, //( I' -> Num
        {5, 14, 5, -14, 999, 999, 999, 999}, //cte lit I'->cte lit
        /* -> */       {5, 17, 5, -17, 8, 999, 999, 999}, //= I'->=K
        {6, 5, 6, -5, 8, 11, 999, 999}, //[ A->[ KE
        /* 20 */       {7, 1, 7, 999, 999, 999, 999, 999},//; A'->e
        {7, 2, 7, 999, 999, 999, 999, 999},//, A'->e
        {7, 5, 7, -5, 8, -6, 7, 999}, //[ A' -> [K]A'
        {7, 12, 7, -12, 999, 999, 999, 999}, //( A' -> (
        {8, 4, 8, -4, 999, 999, 999, 999}, //Id K -> Id
        {8, 5, 8, -5, 8, 11, 999, 999}, //[ K -> [ KE
        {8, 7, 8, -7, 999, 999, 999, 999}, //Num K -> Num
        {8, 21, 8, -21, 999, 999, 999, 999}, //Real K -> Num
        {8, 12, 8, -12, 8, 11, 999, 999}, //( K -> ( KE
        {8, 15, 8, -15, 8, 10, 999, 999}, //{ K -> { KF
        {9, 8, 9, -8, 999, 999, 999, 999}, //char T->Char
        {9, 9, 9, -9, 999, 999, 999, 999}, //int T->int
        {9, 10, 9, -10, 999, 999, 999, 999},//float T->float
        /*segunda gramatica */
        /* 25 */    {10, 11, 10, -11, 11, -1, 999, 999},//puts F-> puts E;
        {10, 16, 10, -16, 999, 999, 999, 999},//} F-> };
        {11, 6, 11, -6, 1, 999, 999, 999},//]E -> ]D
        {11, 12, 11, -12, 12, -13, 999, 999},//( E -> (P)
        {11, 13, 11, -13, 999, 999, 999, 999},//)E -> )
        {12, 14, 12, -14, 999, 999, 999, 999},//cte lit P->cte lit
        {12, 18, 12, -18, 8, 999, 999, 999},//+ P -> + k
        {12, 19, 12, -19, 8, 999, 999, 999},//- P -> - k
        {12, 20, 12, -20, 8, 999, 999, 999},// / P ->/ k
    };


public:
    sintactico(char (*tokens)[100]);
    void vanalisis_sintactico();
    void insertapila(string elem);
    void eliminapila();
    int estoken(char x[]);
    int buscaTabla(char a[], char x[]);
};

#endif // SINTACTICO_H
