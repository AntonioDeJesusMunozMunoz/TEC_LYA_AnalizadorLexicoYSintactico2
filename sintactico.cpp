#include "sintactico.h"

sintactico::sintactico(char (*tokens)[100]) {
    this->tokens = tokens;
    cima = -1;
}

void sintactico::vanalisis_sintactico()
{
    int ip=0, i, j;
    int renglon, iast;
    char x[10], a[10];

    insertapila("$");

    if(strcmp(tokens[ip], "puts") == 0)
        insertapila("F");
    else
        insertapila("D");

    printf("\nSalida del Analizador Sintactico (asTokens): \n");
    printf("Arreglo de Tokens: \n");

    for(i=0; strcmp(tokens[i], "$") != 0; i++)
        printf("%s ", tokens[i]);

    printf("\n\n Producciones: \n");

    do
    {
        strcpy(x, pilac[cima]);
        strcpy(a, tokens[ip]);

        if(estoken(x) || (strcmp(x, "$") == 0))
        {
            if(strcmp(x, a) == 0)
            {
                eliminapila();
                ip++;
            }
            else
            {
                if(strcmp(tokens[ip], "puts") == 0)
                    insertapila("F");
                else //Sino
                    insertapila("D");

                strcpy(x, pilac[cima]);

            }
        }
        else
        {
            renglon = buscaTabla(a, x);

            if(renglon != 999)
            {
                eliminapila();
                iast = 0;
                printf("%-3s -> ", varsint[tablaM[renglon][0]]);

                for(j= 3; iast!=999; j++)
                {
                    iast = tablaM[renglon][j];  //999
                    if(iast < 0)
                    {
                        iast *= -1;
                        printf("%s ",token[iast]);

                    }
                    else
                    {
                        if(iast != 999)
                            printf("%s", varsint[iast]);
                    }
                }

                printf("\n");

                for(i=j-2; i>2; i--)
                {
                    iast = tablaM[renglon][i];
                    if(iast < 0)
                    {
                        iast *= -1;
                        insertapila(token[iast]);
                    }
                    else
                        insertapila(varsint[iast]);
                }
            }
            else
            {
                printf("\n\n Error de Sintaxis");
                return;
            }
        }
    }while(strcmp(x, "$") != 0);
    printf("\n");
}

void sintactico::insertapila(string elem)
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

void sintactico::eliminapila()
{
    if(cima == -1)
        puts("Pila Vacia");
    else{
        strcpy(pilac[cima],"");
        cima--;
    }
}

int sintactico::estoken(char x[])
{
    int i;

    for(i=0; i<23; i++)
    {
        if(strcmp(x, token[i]) == 0)
            return 1;
    }

    return 0;
}

int sintactico::buscaTabla(char a[], char x[])
{
    int indx=0, inda=0, i;

    for(i=0; i<23; i++)
        if(strcmp(a, token[i]) == 0)
            inda = i;//9 int

    for(i=0; i<15; i++)
        if(strcmp(x, varsint[i]) == 0)
            indx=i; //1 D

    for(i=0; i<44; i++)
    {
        if(indx == tablaM[i][0])
            if(inda == tablaM[i][1])
                return i;
    }

    return 999;
}


