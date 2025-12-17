#include "lexico.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <handlefiles.h>


lexico::lexico(FILE* Fd, int numBytesArch) {
    this->Fd = Fd;
    this->numBytesArch = numBytesArch;
}

void lexico::vanalisislexico()
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
    strcpy(asTokens[k], "$"); //es como la 3ra vez que soluciono este bug
}

void lexico::viniedos()
{
    edoAct=0;
    edoIni=0;
}

char lexico::nextchar()
{
    char cAux;
    fread(&cAux,sizeof(cAux),1,Fd);
    indice++;
    return cAux;
}

void lexico::vretract()
{
    indice--;
    fseek(Fd,(long)indice,SEEK_SET);
}

int lexico::edoActesacept()
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

void lexico::falla()
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

void lexico::recuperaerror()
{
    iniToken = indice;
    viniedos();
}

int lexico::esId()
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

void lexico::vmuestra()
{
    int iJ;

    puts("\nTOKENS RECONOCIDOS : \n");
    for(iJ=0; iJ < k; iJ++)  //,Ren++)
    {
        puts(asTokens[iJ]);

    }
}

char (*lexico::getTokens())[100] {
    return asTokens;
}





