
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


#include <iostream>
using namespace std;

//#define TRUE 1
//#define FALSE 0

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

//char *PalRes[]= {"char", "float","int","puts"}; //printf
char PalRes[5][10]= {"char", "float","int","puts"}; //printf

//si se usa objeto string, cambiar el uso de strcmp
//string PalRes[10]= {"char", "float","int","puts"}; //printf

char sLexema[127];
char sLinea[127];
//char *non="13579", *par="24680";
char non[6]="13579", par[6]="24680";
char asTokens [MAXTOKEN][100];
int indice=0, edoAct, edoIni, iniToken=0, k, numBytesArch;

int cima = -1;
char pilac[MAX][10];

void generararch();
void vabrirarch();
int  bytesarch();

void vanalisislexico();
void vanalisis_sintactico();
void viniedos();
char nextchar();
void vretract();
int edoActesacept();
void vmuestra();
void falla();
void recuperaerror();
int esId();

void insertapila(string elem);//(char *elem);  //(char elem[]);
int buscaTabla(char a[], char x[]);
void eliminapila();
int estoken(char x[]);

bool finarch = false;
FILE *Fd;

// AGREGAR EL RECONOCIMIENTO DE NUMEROS REALES
// ERROR EN ESTA APP. NO VALIDA NUMEROS FLOTANTES O REALES

char token[22][8] = {"x", ";", ",", "*", "Id", "[", "]", "Num", "char", "int", "float",
                     "puts", "(", ")", "Cte.Lit", "{", "}", "=","+","-","/", "Real"};

char varsint[15][3]={"x", "D", "L", "L'", "I", "I'", "A", "A'", "K",
                       "T", "F", "E", "P"};
    // e -> cadena vacia         //X  A  ?
int tablaM[100][8]= {             {1, 5, 1, 5, 999, -1, 999, 999}, //[ D->I';
                                  {1, 5, 1, 5, 999, -1, 999, 999}, //; D->I';
                                  {1, 1, 1, 5, 999, -1, 999, 999}, //id D->PL';
                                  {1, 7, 1, 5, 3, -1, 999, 999}, //num D->I'L';
                                  {1, 8, 1, 9, 2, -1, 999, 999}, //char D->TL;
                                  {1, 9, 1, 9, 2, -1, 999, 999}, //int D->TL;
                                  {1, 10, 1, 9, 2, -1, 999, 999}, //float D->TL;
                     /* 5 */      {2, 3, 2, 4, 3, 999, 999, 999}, // * L->IL'
                                  {2, 4, 2, 4, 3, 999, 999, 999}, //Id L->IL'
                                  {3, 1, 3, 5, 999, 999, 999, 999}, //; L'->I'
                                  {3, 1, 3, 999, 999, 999, 999, 999},//; L'->e
                                  {3, 2, 3, -2, 4, 3, 999, 999}, //, L'->,IL'
                    /* 10 */      {3, 3, 3, -3, 8, 3, 999, 999}, //* L'->*KL'
                                  {3, 18, 3, 12, 3, 999, 999, 999}, //+ L'->PL'
                                  {3, 19, 3, 12, 3, 999, 999, 999}, //- L'->PL'
                                  {3, 20, 3, 12, 3, 999, 999, 999}, // / L'->PL'
                                  {3, 14, 3, -14, 5, 999, 999, 999},// cte. Lit. L'->cte Lit. I'
                                  {4, 3, 4, -3, -4, 5, 999, 999}, // * I->*Id I'
                                  {4, 4, 4, -4, 5, 999, 999, 999},// Id I->Id I'
                                  {5, 1, 5, 999, 999, 999, 999, 999},// ; I'->e
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
                                  {11, 18, 11, 12,  11, 999, 999, 999},//+E -> PE (ESTA SE LA PUSE YO TONIO
                                  {12, 14, 12, -14, 999, 999, 999, 999},//cte lit P->cte lit
                                  {12, 18, 12, -18, 8, 999, 999, 999},//+ P -> + k
                                  {12, 19, 12, -19, 8, 999, 999, 999},//- P -> - k
                                  {12, 20, 12, -20, 8, 999, 999, 999},// / P ->/ k  
};


int main(void)
{
    char resp;
    do
    {
        /*CREACIÓN DEL ARCHIVO*/
        //leo entrada
        puts("Desea Generar el Archivo (s/n) : ");
        resp = cin.get();

        //si dijo que si, genero el archivo
        if(strchr("Ss",resp))
            generararch();

        /*LECTURA DE ARCHIVO*/
        vabrirarch();
        numBytesArch= bytesarch();

        //si no tiene datos, le digo
        if(numBytesArch==0)
        {
            printf("El archivo NO Tiene Datos. Pulse una tecla");
            if(cin.get() == 0) //  getch()==0)
            { cin.get();//getch();
                exit(-1);
            }
        }
        //si si tiene, corro el analizador léxico
        else{
            vanalisislexico();
        }
        fclose(Fd);


        /*MUESTRA DEL RESULTADO DEL ANALIZADOR LÉXICO*/
        printf("Salida del Analizador Lexico (asTokens)");
        vmuestra();


        /*ANALIZADOR SINTÁCTICO*/
        printf("Pulse una tecla para continuar");
        if(cin.get() == 0) //getch()==0)
            cin.get();     //getch();
        vanalisis_sintactico();
        cin.get();


        /*S PARA CONTINUAR*/
        printf("continuar (s/n)? : " );
        cin>>resp;
        cin.get();

    }while (strchr("Ss",resp));

    return 0;
}
void generararch()
{
    /*VARIABLES NECESARIAS*/
    char car;
    char nomArch[100];
    string nombre;


    /*LEO NOMBRE*/
    printf("Nombre del Archivo a GENERAR (sin extension): ");
    cin>>nombre;
    cin.get();    //ELIMINAR ENTER


    /*ABRO ARCHIVO*/
    sprintf(nomArch,"%s.dat",nombre.c_str());
    Fd = fopen(nomArch,"w+b");
    if(Fd == nullptr)
    {
        cout<<"NO SE PUEDE ABRIR EL ARCHIVO : "<<nomArch;
        exit(-1);
    }

    printf("teclea el archivo (<@> para terminar el archivo): \n");


    /*LOOP PARA GUARDAR LO ESCRITO EN ARCHIVO*/
    do
    {
        //Leo caracter
        car = cin.get();

        //si es \n, salto linea
        //if( car == '\n')
        //    printf("\n");

        //si no es @ o BACKSPACE, lo escribe
        if(car != '@' && car != 8)
            fwrite(&car,sizeof(car),1,Fd);

    //continua mientras no sea @
    }while(car != '@');

    //cierra archivo
    fclose(Fd);
}

void vabrirarch()
{
    /*VARIABLES NECESARIAS*/
    char nomArch[100];
    char *nombre = new char[100];


    /*LEO EL ARCHIVO*/
    printf("\n\n Nombre del Archivo a ABRIR(sin extension): ");
    cin.get();                      //ELIMINAR EL ENTER
    cin.getline(nombre,100,'\n');


    //le añado .dat en vez de .txt
    sprintf(nomArch,"%s.dat",nombre);

    //lo abro como binario con lectura y escritura
    Fd = fopen(nomArch,"r+b");

    //si no lo pudo abrir
    if(Fd==NULL)
    {
        //ERROR
        printf("NO SE PUEDE ABRIR EL ARCHIVO");
        exit(-1);    //cin.get();

    }
    //si si pudo
    else
    {
        printf("EL ARCHIVO SE ENCUENTRA ABIERTO \n");

    }

}

int bytesarch()
{
    /*ESTE METODO LEE LA LONGITUD EN EL ARCHIVO*/
    int aux;
    fseek(Fd,0L,SEEK_END);
    aux = (int) ftell(Fd);
    fseek(Fd,0L,SEEK_SET);
    return aux;
}

void vanalisislexico()
{
    char cCarent;

    indice = iniToken = k = 0;
    viniedos();

    while(indice < numBytesArch || edoActesacept())
    {
        switch(edoAct)
        {
        case 0: cCarent=nextchar();
            if (strchr(non,cCarent))
                edoAct = 1;
            else
                if(strchr(par,cCarent))
                    edoAct = 2;
                else
                    if(cCarent == '.')
                        edoAct = 37;
                    else
                        falla();
            break;

        case 1: cCarent=nextchar();
            if(strchr(non,cCarent))
                edoAct=1;
            else
                if(strchr(par,cCarent))
                    edoAct = 2;
                else if(cCarent== '.')
                    edoAct = 37;
                else
                    falla();
            break;

        case 2: cCarent=nextchar();
            if(strchr(non,cCarent))
                edoAct=1;
            else
                if (strchr(par,cCarent))
                    edoAct=2;
                else if(cCarent== '.')
                    edoAct = 37;
                else
                    edoAct=3;
            break;

        case 3: vretract();
            strcpy(asTokens[k++],"Num");
            if (indice >= numBytesArch)
                return;
            iniToken=indice;
            viniedos();
            break;

        case 4: cCarent=nextchar();
            switch(cCarent)
            {
            case '+': edoAct=5; break;
            case '-': edoAct=6; break;
            case '*': edoAct=7; break;
            case '/': edoAct=8; break;
            default: falla();
            }
            break;

        case 5: strcpy(asTokens[k++], "+");
            if (indice >= numBytesArch)
                return;
            iniToken=indice;
            viniedos();
            break;

        case 6: strcpy(asTokens[k++], "-");
            if (indice>=numBytesArch)
                return;
            iniToken=indice;
            viniedos();
            break;

        case 7: strcpy(asTokens[k++], "*");
            if (indice>=numBytesArch)
                return;
            iniToken=indice;
            viniedos();
            break;

        case 8: strcpy(asTokens[k++], "/");
            if (indice>=numBytesArch)
                return;
            iniToken=indice;
            viniedos();
            break;


        case 9: cCarent=nextchar();
            if (strchr(par,cCarent))
                edoAct=10;
            else
                if(strchr(non,cCarent))
                    edoAct=11;
                else if(cCarent== '.')
                    edoAct = 37;
                else
                    falla();
            break;

        case 10: cCarent=nextchar();
            if (strchr(par,cCarent))
                edoAct=10;
            else
                if(strchr(non,cCarent))
                    edoAct=11;
                else if(cCarent== '.')
                    edoAct = 37;
                else
                    falla();
            break;

        case 11 : cCarent=nextchar();
            if (strchr(non,cCarent))
                edoAct=11;
            else
                if(strchr(par,cCarent))
                    edoAct=10;
                else if(cCarent== '.')
                    edoAct = 37;
                else
                    edoAct=12;
            break;

            // NON - PAR
        case 12: vretract();
            strcpy(asTokens[k++],"Num");
            if (indice>=numBytesArch)
                return;
            iniToken=indice;
            viniedos();
            break;

        case 13: cCarent=nextchar();
            if ((isalpha(cCarent)|| cCarent=='_'))
                edoAct=14;
            else
                falla();
            break;

        case 14: cCarent=nextchar();
            if ((isalpha(cCarent)|| cCarent=='_') || isdigit(cCarent))
                edoAct=14;
            else
                edoAct= 15;
            break;

        case 15: vretract();
            if(esId())
                strcpy(asTokens[k++], "Id");
            else
                strcpy(asTokens[k++],sLexema);

            if(indice>=numBytesArch)
                return;
            iniToken=indice;
            viniedos();
            break;


        case 16: cCarent=nextchar();
            if(cCarent==';')
                edoAct=17;
            else
                falla();
            break;

            /* Al encontrar el caracter ';' , que indica fin de linea,
                 Se copia el caracter '$' al fin del arreglo astokens
                 */
        case 17: strcpy(asTokens[k++], ";");
            strcpy(asTokens[k], "$");
            if (indice >= numBytesArch)
                return;
            iniToken=indice;
            viniedos();
            break;

        case 18: cCarent=nextchar();
            if(cCarent=='[')
                edoAct=19;
            else
                falla();
            break;

        case 19: strcpy(asTokens[k++], "[");
            if (indice >= numBytesArch)
                return;
            iniToken=indice;
            viniedos();
            break;

        case 20: cCarent=nextchar();
            if(cCarent==']')
                edoAct=21;
            else
                falla();
            break;

        case 21: strcpy(asTokens[k++], "]");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;

        case 22: cCarent = nextchar();
            if(cCarent == ',')
                edoAct=23;
            else
                falla();
            break;

        case 23: strcpy(asTokens[k++], ",");
            if (indice >= numBytesArch)
                return;
            iniToken=indice;
            viniedos();
            break;

        case 24: cCarent = nextchar();
            if (('"' == cCarent) && cCarent)
                edoAct=25;
            else
                falla();
            break;

        case 25: cCarent=nextchar();
            if (('"' != cCarent) && cCarent)
                edoAct=25;
            else
                if(cCarent)
                    edoAct=26;
            break;

        case 26: strcpy(asTokens[k++],"Cte.Lit");
            if (indice >= numBytesArch)
                return;
            iniToken=indice;
            viniedos();
            break;

        case 27: cCarent=nextchar();
            if(cCarent == '(')
                edoAct=28;
            else
                falla();
            break;

        case 28: strcpy(asTokens[k++], "(");
            if (indice>=numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;

        case 29:cCarent=nextchar();
            if(cCarent == ')')
                edoAct=30;
            else
                falla();
            break;

        case 30: strcpy(asTokens[k++], ")");
            if (indice>=numBytesArch)
                return;
            iniToken=indice;
            viniedos();
            break;

        case 31: cCarent = nextchar();
            if(cCarent == '{')
                edoAct = 32;
            else
                falla();
            break;

        case 32: strcpy(asTokens[k++], "{");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;

        case 33: cCarent = nextchar();
            if(cCarent == '}')
                edoAct = 34;
            else
                falla();
            break;

        case 34: strcpy(asTokens[k++], "}");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;

        case 35: cCarent = nextchar();
            if(cCarent == '=')
                edoAct = 36;
            else
                falla();
            break;

        case 36: strcpy(asTokens[k++], "=");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;

        case 37: cCarent=nextchar();
            if (strchr(non,cCarent))
                edoAct = 38;
            else
                if(strchr(par,cCarent))
                    edoAct = 39;
                else
                    falla();
            break;
        case 38: cCarent=nextchar();
            if(strchr(non,cCarent))
                edoAct=38;
            else
                if(strchr(par,cCarent))
                    edoAct = 39;
                else
                    edoAct=40;
            break;

        case 39: cCarent=nextchar();
            if(strchr(non,cCarent))
                edoAct=38;
            else
                if (strchr(par,cCarent))
                    edoAct=39;
                else
                    edoAct=40;
            break;
        case 40: vretract();
            strcpy(asTokens[k++],"Real");
            if (indice >= numBytesArch)
                return;
            iniToken=indice;
            viniedos();
            break;
        }/*switch*/
    } /*while*/
    strcpy(asTokens[k], "$");
}
void viniedos()
{
    edoAct=0;
    edoIni=0;
}
char nextchar()
{
    char cAux;
    fread(&cAux,sizeof(cAux),1,Fd);
    indice++;
    return cAux;
}
void vretract()
{
    indice--;
    fseek(Fd,(long)indice,SEEK_SET);
}

int edoActesacept()
{
    switch (edoAct){
    case 8: case 5: case 7: case 6: case 3:
    case 12: case 15: case 17: case 19: case 21:
    case 23 : case 26: case 28: case 30: case 32:
    case 34: case 36: case 40:
        return true;
    default : return false;
    }
}

void falla()
{
    switch (edoIni)
    {
    case 0 : edoIni=4;
        indice=iniToken;
        fseek(Fd, (long)iniToken, SEEK_SET);
        break;

    case 4 : edoIni=9;
        indice=iniToken;
        fseek(Fd, (long)iniToken, SEEK_SET);
        break;

    case 9 : edoIni=13;
        indice=iniToken;
        fseek(Fd, (long)iniToken, SEEK_SET);
        break;

    case 13 : edoIni=16;
        indice = iniToken;
        fseek(Fd, (long)iniToken, SEEK_SET);
        break;

    case 16 : edoIni=18;
        indice = iniToken;
        fseek(Fd, (long)iniToken, SEEK_SET);
        break;

    case 18 : edoIni=20;
        indice=iniToken;
        fseek(Fd, (long)iniToken, SEEK_SET);
        break;

    case 20 : edoIni=22;
        indice = iniToken;
        fseek(Fd, (long)iniToken, SEEK_SET);
        break;

    case 22 : edoIni=24;
        indice = iniToken;
        fseek(Fd, (long)iniToken, SEEK_SET);
        break;

    case 24 : edoIni=27;
        indice = iniToken;
        fseek(Fd, (long)iniToken, SEEK_SET);
        break;

    case 27 : edoIni=29;
        indice = iniToken;
        fseek(Fd, (long)iniToken, SEEK_SET);
        break;

    case 29: edoIni = 31;
        indice = iniToken;
        fseek(Fd, (long)iniToken, SEEK_SET);
        break;

    case 31: edoIni = 33;
        indice = iniToken;
        fseek(Fd, (long)iniToken, SEEK_SET);
        break;

    case 33: edoIni = 35;
        indice = iniToken;
        fseek(Fd, (long)iniToken, SEEK_SET);
        break;

    case 35: recuperaerror();
    }

    edoAct=edoIni;
}

void recuperaerror()
{
    iniToken = indice;
    viniedos();
}

int esId()
{
    int n,m,found = false;
    fseek(Fd,(long)iniToken,SEEK_SET);
    for (m=iniToken, n=0; m<indice ; m++, n++)
        fread(&sLexema[n],sizeof(char),1, Fd);
    sLexema[n]= '\0';
    for (m=0 ; m < NUMPALRES && !found ;)
        if (strcmp(PalRes[m], sLexema)==0)
            found = true;
        else
            m++;
    return (found ? 0 : 1);
}


void vmuestra()
{
    int iJ;

    puts("\nTOKENS RECONOCIDOS : \n");
    for(iJ=0; iJ < k; iJ++)  //,Ren++)
    {
        puts(asTokens[iJ]);

    }
}


void vanalisis_sintactico()
{
    /*LAS VARIABLES QUE VOY A USAR*/
    int ip=0, i, j;
    int renglon, iast;
    char x[10], a[10];  //las que se usaran para la tablaM

    //la pila inicia con un $ como en la teoria
    insertapila("$");

    //si la primer token es puts, se usa la gramatica extendida (iniciar con F en vez de D)
    if(strcmp(asTokens[ip], "puts") == 0)
        insertapila("F");
    else
        insertapila("D");

    /*IMPRIMIMOS TODOS LOS TOKEN*/
    printf("\nSalida del Analizador Sintactico (asTokens): \n");
    printf("Arreglo de Tokens: \n");

    for(i=0; strcmp(asTokens[i], "$") != 0; i++)
        printf("%s ", asTokens[i]);

    /*CONSEGUIMOS E IMPRIMIMOS LAS PRODUCCIONES*/
    printf("\n\n Producciones: \n");

    do
    {
        //consigo el primer caracter en la pila y en a
        strcpy(x, pilac[cima]);
        strcpy(a, asTokens[ip]);

        //si es terminal o $
        if(estoken(x) || (strcmp(x, "$") == 0))
        {
            //si son iguales, los elimino
            if(strcmp(x, a) == 0)
            {
                eliminapila();
                ip++;
            }

            //si no
            else
            {
                //vuelvo a añadir el simbolo inicial?
                if(strcmp(asTokens[ip], "puts") == 0)
                    insertapila("F");
                else
                    insertapila("D");

                strcpy(x, pilac[cima]);

            }
        }
        else
        {
            //consigo el renglón donde esta la prod
            renglon = buscaTabla(a, x);

            //si no es vacio
            if(renglon != 999)
            {
                //elimino el token de la pila
                eliminapila();
                iast = 0;

                /*PRINTEAR PROD*/
                //printeo el lado izquierdo de la prod (siempre en j = 0)
                printf("%-3s -> ", varsint[tablaM[renglon][0]]);

                //recorro ese renglón de la tabla M, saltando los espacios que uso para otras cosas
                for(j= 3; iast!=999; j++)
                {

                    //consigo la i del caracter que voy a imprimir
                    iast = tablaM[renglon][j];
                    //si es negativo, es terminal
                    if(iast < 0)
                    {
                        iast *= -1;
                        printf("%s ",token[iast]);

                    }
                    //si es positivo, es no terminal
                    else
                    {
                        if(iast != 999)
                            printf("%s", varsint[iast]);
                    }
                }

                //salto linea
                printf("\n");

                /*METER LA PROD A LA PILA*/
                for(i=j-2; i>2; i--)
                {
                    //si es negativo, inserto un token terminal
                    iast = tablaM[renglon][i];
                    if(iast < 0)
                    {
                        iast *= -1;
                        insertapila(token[iast]);
                    }

                    //si no, inserto el token terminal
                    else
                        insertapila(varsint[iast]);
                }
            }

            //si si es vacio, es sintaxis invalida
            else
            {
                printf("\n\n Error de Sintaxis");
                return;
            }
        }
    }while(strcmp(x, "$") != 0);
    printf("\nSintaxis valida\n");
}

void insertapila(string elem)//(char *elem) //(char elem[])
{
    if(cima == -1){
        cima = 0;
        strcpy(pilac[cima],elem.c_str());
    }
    else{
        if(cima == MAX - 1)
            puts("Pila LLena");
        else{
            cima++;
            strcpy(pilac[cima],elem.c_str());
        }
    }
}

void eliminapila()
{
    if(cima == -1)
        puts("Pila Vacia");
    else{
        strcpy(pilac[cima],"");
        cima--;
    }
}

int estoken(char x[])
{
    int i;

    for(i=0; i<23; i++)
    {
        if(strcmp(x, token[i]) == 0)
            return 1;
    }

    return 0;
}

int buscaTabla(char a[], char x[])
{
    int indx=0, inda=0, i;

    /*CONSIGO CUAL INDICE CORRESPONDE A EL TOKEN EN A*/
    for(i=0; i<23; i++)
        if(strcmp(a, token[i]) == 0)
            inda = i;//9 int

    /*CONSIGO CUAL INDICE CORRESPONDE A EL TOKEN EN X*/
    for(i=0; i<15; i++)
        if(strcmp(x, varsint[i]) == 0)
            indx=i; //1 D

    /*RECORRO LOS PRIMEROS 44 RENGLONES DE LA TABLA PORQUE SOLO USO ESOS*/
    for(i=0; i<50; i++)
    {
        /*SI EL INDX Y EL INDA CONCUERDAN CON LOS VALORES EN ALGUN RENGLON, ESE RENGLON TIENE LA PROD*/
        if(indx == tablaM[i][0])
            if(inda == tablaM[i][1])
                return i; /*REGRESO EL INDICE DEL RENGLON DND ESTA LA PROD*/
    }

    /*SI NO COINCIDE, REGRESO 999 QUE SE ENTIENDE COMO ERROR*/
    return 999;
}

