#include "analizadorlexico.h"
#include <iostream>
#include <string.h>
#include <fstream>

void AnalizadorLexico::scanFile(string path)
{
    string cadenaHelper;
    ifstream datos(path);
    if(datos.fail())
        cout<<"Archivo no EXISTE"<<endl;
    else
    {
        while(!datos.eof())
        {
            getline(datos,cadenaHelper);
            if(cadenaHelper == "")
                break;
            cout<<endl<<cadenaHelper<<endl;
            cadenaHelper += ";";
            scan(cadenaHelper);
            cout<<endl;
            cout<<">>>>>>><<<<<<<<"<<endl;
        }
    }
}

void AnalizadorLexico::superEditor()
{
    cout<<"SUPER EDITOR, PARA TERMINAR ENTER EN LINEA NUEVA"<<endl;
    cout<<"Finaliza cada linea con (ENTER) "<<endl;
    string cadenaS;
    cin.ignore();
    for(ren = 0; ren < 22; ren++)
    {
        cout<< ren + 1<<" : ";
        getline(cin,cadenaS,'\n');
        strncpy(editor[ren], cadenaS.c_str(), sizeof(editor[ren]));
        //strdup()
        if(strcmp(editor[ren],"") == 0)
            break;
    }
    int indice = 0;
    while(indice < ren)
    {
        string currS = editor[indice++];
        currS += ";";
        scan(currS);
        cout<<"-----------------------------"<<endl;
    }

    //reseteo la variable
    ren = 0;
}

void AnalizadorLexico::scan(string cadena)
{
    this->currCadena = cadena;
    char caracter;
    inicializaEstados();
    i = inicioToken = 0;
    //RECORRER LA CADENA IDENTIFICANDO SI ES :  DELIMITADOR, IDENT, NUMERO
    while( i < strlen(cadena.c_str()) || estadoDeAceptacion() )
    {
        switch( estadoActual )
        {
        case 0: caracter = leerCar();
            if(esDelimitador(caracter))
                estadoActual = 1;
            else
                fallo();  // CAMBIA ESTADO
            break;
        case 1: caracter = leerCar();
            if(esDelimitador(caracter))
                estadoActual = 1;
            else
                estadoActual = 2;
            break;
        case 2:  retrocederCar();
            cout<<"DELIMITADOR"<<endl;
            inicializaEstados();
            inicioToken = i;
            //       " int _i = 0;"
            break;

        case 3:  // IDENTIFICADORES
        {
            caracter = leerCar();
            if(esLetra(caracter) || caracter == '_' )
                estadoActual = 4;
            else
                fallo();  // CAMBIA ESTADO
        }
        break;
        case 4: caracter = leerCar();
            if(esLetra(caracter) || esDigito(caracter) || caracter == '_')
                estadoActual = 4;     // float fact;
            else
                estadoActual = 5;
            break;
        case 5:
        {
            retrocederCar();
            cout<<"IDENTIFICADOR"<<endl;
            inicializaEstados();
            inicioToken = i;
        }
        break;

        case 6:    //NUMEROS ENTEROS Y REALES
            caracter = leerCar();
            if(esDigito(caracter))
                estadoActual = 7;
            else
                fallo();
            break;
        case 7:    caracter = leerCar();
            if(esDigito(caracter))
                estadoActual = 7;
            else if( caracter == '.')
                estadoActual = 9;
            else
                estadoActual = 8;
            break;
        case 8: retrocederCar();
            cout<<"NUMERO ENTERO"<<endl;
            inicializaEstados();
            inicioToken = i;
            break;
        case 9: caracter = leerCar();
            if(esDigito(caracter))
                estadoActual = 9;
            else
                estadoActual = 10;
            break;
        case 10: retrocederCar();
            cout<<"NUMERO REAL"<<endl;
            inicializaEstados();
            inicioToken = i;
            break;
            // OPERADORES  = y ==
        case 11: caracter = leerCar();
            if(caracter == '=')
                estadoActual = 12;
            else
                fallo();
            break;
        case 12: caracter = leerCar();
            if(caracter == '=')
                estadoActual = 14;
            else
                estadoActual = 13;
            break;
        case 13: retrocederCar();
            cout<<"OPERADOR ASIGNACION"<<endl;
            inicioToken = i;
            inicializaEstados();
            break;
        case 14:
            // retrocederCar;
            //caracter = leerCar(i);
            cout<<"OPERADOR RELACIONAL "<<endl;
            inicializaEstados();
            inicioToken = i;
            break;

            // OPERADOR ! (NOT)   .   !=
        case 15: caracter = leerCar();
            if( caracter == '!')
                estadoActual = 16;
            else
                fallo();
            break;
        case 16 : caracter = leerCar();
            if(caracter == '=')
                estadoActual = 18;  //   <----
            else
                estadoActual = 17;
            break;
        case 17: retrocederCar();
            cout<<"\nOperador Logico"<<endl;
            inicializaEstados();
            inicioToken = i;
            break;
        case 18:
            cout<<"Operador Relacional"<<endl;
            inicializaEstados();
            inicioToken = i;
            break;
            // OPERADOR > , >=
        case 19: caracter = leerCar();
            if(caracter == '>')
                estadoActual = 20;
            else
                fallo();
            break;
        case 20 : caracter = leerCar();
            if(caracter == '=')
                estadoActual = 22;
            else
                estadoActual = 21;
            break;
        case 21 : retrocederCar();
            cout<<"Operador Relacional"<<endl;
            inicializaEstados();
            inicioToken = i;
            break;
        case 22:
            cout<<"Operador Relacional"<<endl;
            inicializaEstados();
            inicioToken = i;
            break;

            // OPRADOR  < , <=
        case 23:
            caracter = leerCar();
            if(caracter == '<')
                estadoActual = 24;
            else
                fallo();
            break;
        case 24: caracter = leerCar();
            if(caracter == '=')
                estadoActual = 26;
            else
                estadoActual = 25;
            break;
        case 25: retrocederCar();
            cout<<"Operador Relacional"<<endl;
            inicializaEstados();
            inicioToken = i;
            break;
        case 26:
            cout<<"Operador Relacional"<<endl;
            inicializaEstados();
            inicioToken = i;
            break;

            //   OPERADORES ARITMETICOS
        case 27:caracter = leerCar();
            if(caracter == '+')
                estadoActual = 28;
            else
                fallo();
            break;
        case 28: cout<<"Operador Aritmetico"<<endl;
            inicializaEstados();
            inicioToken = i;
            break;
        case 29:caracter = leerCar();
            if(caracter == '-')
                estadoActual = 30;
            else
                fallo();
            break;
        case 30: cout<<"Operador Aritmetico"<<endl;
            inicializaEstados();
            inicioToken = i;
            break;
        case 31:caracter = leerCar();
            if(caracter == '*')
                estadoActual = 32;
            else
                fallo();
            break;
        case 32: cout<<"Operador Aritmetico"<<endl;
            inicializaEstados();
            inicioToken = i;
            break;
        case 33:caracter = leerCar();
            if(caracter == '/')
                estadoActual = 34;
            else
                fallo();
            break;
        case 34: cout<<"Operador Aritmetico"<<endl;
            inicializaEstados();
            inicioToken = i;
            break;
        case 35:caracter = leerCar();
            if(caracter == '%')
                estadoActual = 36;
            else
                fallo();
            break;
        case 36: cout<<"Operador Aritmetico"<<endl;
            inicializaEstados();
            inicioToken = i;
            break;


        }//FIN SWITCH

    }//FIN WHILE

}// FIN
void AnalizadorLexico::inicializaEstados()
{
   estadoInicial = estadoActual = 0;
}

void AnalizadorLexico::fallo()
{
    switch(estadoInicial)
    {
    case 0: {
        estadoInicial = 3;
        i = inicioToken;
    }
    break;

    case 3: {
        estadoInicial = 6;
        i = inicioToken;
    }
    break;
    case 6: estadoInicial = 11;
        i = inicioToken;
        break;
    case 11: estadoInicial = 15;
        i = inicioToken;
        break;
    case 15: estadoInicial = 19;
        i = inicioToken;
        break;
    case 19: estadoInicial = 23;
        i = inicioToken;
        break;
    case 23: estadoInicial = 27;
        i = inicioToken;
        break;
    case 27 : estadoInicial = 29;
        i = inicioToken;
        break;
    case 29: estadoInicial = 31;
        i = inicioToken;
        break;
    case 31: estadoInicial = 33;
        i = inicioToken;
        break;
    case 33: estadoInicial = 35;
        i = inicioToken;
        break;
    }
    estadoActual = estadoInicial;
}

bool AnalizadorLexico::estadoDeAceptacion()
{
    switch(estadoActual){
        case 2:
        case 5:
        case 8:
        case 10:
        case 13:
        case 14:
        case 17:
        case 18:
        case 21:
        case 22:
        case 25:
        case 26:
        case 28:
        case 30:
        case 32:
        case 34:
        case 36:
            return true;

        default :  return false;
    }
}

void AnalizadorLexico::retrocederCar()
{
    this->i--;
}

char AnalizadorLexico::leerCar()
{
    char c = this->currCadena[this->i++];
    return c;
}

bool AnalizadorLexico::esDelimitador(char c)
{
    return  (c== ' ' || c=='\t'|| c =='\n');
}

bool AnalizadorLexico::esLetra(char c)
{
    if( (c>= 97 && c<= 122) || (c>='A' && c <= 'Z'))
        return true;
    return false;
}

bool AnalizadorLexico::esDigito(char c)
{
    return c>='0' && c <='9';
}
