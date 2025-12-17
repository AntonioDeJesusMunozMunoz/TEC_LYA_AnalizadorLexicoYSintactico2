#ifndef ANALIZADORLEXICO_H
#define ANALIZADORLEXICO_H

#include <string>

using namespace std;

class AnalizadorLexico
{
public:
    void scanFile(string path);
    void superEditor();
    void scan(string cadena);
private:
    //vars
    int i, inicioToken, estadoInicial, estadoActual;
    string currCadena;

    char editor[22][255];
    int ren;

    //helpers
    void inicializaEstados();
    void fallo();
    bool estadoDeAceptacion();
    void retrocederCar();
    char leerCar();

    //identificadores
    bool esDelimitador(char c);
    bool esLetra(char c);
    bool esDigito(char c);
};

#endif // ANALIZADORLEXICO_H
