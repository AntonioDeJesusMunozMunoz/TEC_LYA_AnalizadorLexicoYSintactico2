#include "sintactico.h"

sintactico::sintactico(char (*tokens)[100]) {
    this->tokens = tokens;
    cima = -1;
    cargarProducciones();
}

void sintactico::cargarProducciones()
{
    //LINEA DE D (CAMBIOS PARA PUNTO Y COMA Y NUEVAS SENTENCIAS)
    tablaM[NT_D][TOK_ID].cuerpo    = {{NO_TERMINAL, NT_P}, {NO_TERMINAL, NT_L}         , {TERMINAL, TOK_PUNTOYCOMA}, {NO_TERMINAL, NT_D}};
    tablaM[NT_D][TOK_PUNTOYCOMA].cuerpo = {{NO_TERMINAL, NT_IP}                        , {TERMINAL, TOK_PUNTOYCOMA}, {NO_TERMINAL, NT_D}};
    tablaM[NT_D][TOK_CORCHETEIZQ].cuerpo = {{NO_TERMINAL, NT_IP}                       , {TERMINAL, TOK_PUNTOYCOMA}, {NO_TERMINAL, NT_D}};
    tablaM[NT_D][TOK_NUM].cuerpo   = {{NO_TERMINAL, NT_IP}, {NO_TERMINAL, NT_LP}       , {TERMINAL, TOK_PUNTOYCOMA}, {NO_TERMINAL, NT_D}};
    tablaM[NT_D][TOK_CHAR].cuerpo  = {{NO_TERMINAL, NT_T}                              , {TERMINAL, TOK_PUNTOYCOMA}, {NO_TERMINAL, NT_D}};
    tablaM[NT_D][TOK_INT].cuerpo   = {{NO_TERMINAL, NT_T}                              , {TERMINAL, TOK_PUNTOYCOMA}, {NO_TERMINAL, NT_D}};
    tablaM[NT_D][TOK_FLOAT].cuerpo = {{NO_TERMINAL, NT_T}                              , {TERMINAL, TOK_PUNTOYCOMA}, {NO_TERMINAL, NT_D}};

    //PARA TERMINAR
    tablaM[NT_D][TOK_$].cuerpo = {{TERMINAL, TOK_e}};


    //LINEA DE L
    tablaM[NT_L][TOK_ID].cuerpo       = {{NO_TERMINAL, NT_I}, {NO_TERMINAL, NT_LP}};
    tablaM[NT_L][TOK_ASTERISCO].cuerpo = {{NO_TERMINAL, NT_I}, {NO_TERMINAL, NT_LP}};

    //LINEA DE L'
    tablaM[NT_LP][TOK_MAS].cuerpo     = {{NO_TERMINAL, NT_P}, {NO_TERMINAL, NT_LP}};
    tablaM[NT_LP][TOK_MENOS].cuerpo   = {{NO_TERMINAL, NT_P}, {NO_TERMINAL, NT_LP}};
    tablaM[NT_LP][TOK_DIVISION].cuerpo= {{NO_TERMINAL, NT_P}, {NO_TERMINAL, NT_LP}};
    tablaM[NT_LP][TOK_ASTERISCO].cuerpo = {{TERMINAL, TOK_ASTERISCO}, {NO_TERMINAL, NT_K}, {NO_TERMINAL, NT_LP}};
    tablaM[NT_LP][TOK_PUNTOYCOMA].cuerpo = {{NO_TERMINAL, NT_IP}};
    //tablaM[NT_LP][TOK_CORCHETEDER].cuerpo = {{TERMINAL, TOK_e}};
    tablaM[NT_LP][TOK_COMA].cuerpo = {{NO_TERMINAL, NT_I}, {NO_TERMINAL, NT_LP}};
    tablaM[NT_LP][TOK_CTE_LIT].cuerpo = {{TERMINAL, TOK_CTE_LIT}, {NO_TERMINAL, NT_IP}};

    //LINEA DE I
    tablaM[NT_I][TOK_ASTERISCO].cuerpo = {{TERMINAL, TOK_ASTERISCO}, {TERMINAL, TOK_ID}, {NO_TERMINAL, NT_IP}};
    tablaM[NT_I][TOK_ID].cuerpo = {{TERMINAL, TOK_ID}, {NO_TERMINAL, NT_IP}};


    //LINEA DE IP
    tablaM[NT_IP][TOK_PUNTOYCOMA].cuerpo = {{TERMINAL, TOK_e}};
    tablaM[NT_IP][TOK_COMA].cuerpo       = {{TERMINAL, TOK_e}};
    tablaM[NT_IP][TOK_CORCHETEIZQ].cuerpo = {{NO_TERMINAL, NT_A}};
    tablaM[NT_IP][TOK_IGUAL].cuerpo = {{TERMINAL, TOK_IGUAL}, {NO_TERMINAL, NT_K}};
    tablaM[NT_IP][TOK_CTE_LIT].cuerpo = {{TERMINAL, TOK_CTE_LIT}};

    //LINEA DE A
    tablaM[NT_A][TOK_CORCHETEIZQ].cuerpo = {{TERMINAL, TOK_CORCHETEIZQ},{NO_TERMINAL, NT_K},{NO_TERMINAL, NT_E}};

    //LINEA DE A'
    tablaM[NT_AP][TOK_PUNTOYCOMA].cuerpo = {{TERMINAL, TOK_e}};
    tablaM[NT_AP][TOK_COMA].cuerpo       = {{TERMINAL, TOK_e}};
    tablaM[NT_AP][TOK_PARENTESISIZQ].cuerpo = {{TERMINAL, TOK_PARENTESISIZQ}};
    tablaM[NT_AP][TOK_CORCHETEIZQ].cuerpo = {{TERMINAL, TOK_CORCHETEIZQ}, {TERMINAL, TOK_NUM}, {TERMINAL, TOK_CORCHETEDER}, {NO_TERMINAL, NT_AP}};

    //LINEA DE K
    tablaM[NT_K][TOK_ID].cuerpo   = {{TERMINAL, TOK_ID}};
    tablaM[NT_K][TOK_NUM].cuerpo  = {{TERMINAL, TOK_NUM}};
    tablaM[NT_K][TOK_REAL].cuerpo = {{TERMINAL, TOK_REAL}};
    tablaM[NT_K][TOK_PARENTESISIZQ].cuerpo = {{TERMINAL, TOK_PARENTESISIZQ}, {NO_TERMINAL, NT_K}, {NO_TERMINAL, NT_E}};
    tablaM[NT_K][TOK_LLAVEIZQ].cuerpo = {{TERMINAL, TOK_LLAVEIZQ}, {NO_TERMINAL, NT_K}, {NO_TERMINAL, NT_F}};
    tablaM[NT_K][TOK_CORCHETEIZQ].cuerpo = {{TERMINAL, TOK_CORCHETEIZQ}, {NO_TERMINAL, NT_K}, {NO_TERMINAL, NT_E}};

    //LINEA DE T
    tablaM[NT_T][TOK_CHAR].cuerpo  = {{TERMINAL, TOK_CHAR}, {NO_TERMINAL, NT_TP}};
    tablaM[NT_T][TOK_INT].cuerpo   = {{TERMINAL, TOK_INT},  {NO_TERMINAL, NT_TP}};
    tablaM[NT_T][TOK_FLOAT].cuerpo = {{TERMINAL, TOK_FLOAT},{NO_TERMINAL, NT_TP}};

    //LINEA DE T'
    tablaM[NT_TP][TOK_ID].cuerpo = {{NO_TERMINAL, NT_L}};
    tablaM[NT_TP][TOK_ASTERISCO].cuerpo = {{TERMINAL, TOK_ASTERISCO}, {NO_TERMINAL, NT_Ep}, {TERMINAL, TOK_ID}, {NO_TERMINAL, NT_Dp}};
    tablaM[NT_TP][TOK_CORCHETEIZQ].cuerpo = {{TERMINAL, TOK_CORCHETEIZQ}, {NO_TERMINAL, NT_TPP}};

    //LINEA DE T''
    tablaM[NT_TPP][TOK_CORCHETEDER].cuerpo = {{TERMINAL, TOK_CORCHETEDER}, {TERMINAL, TOK_ID}};
    tablaM[NT_TPP][TOK_NUM].cuerpo = {{TERMINAL, TOK_NUM}, {TERMINAL, TOK_CORCHETEDER}, {NO_TERMINAL, NT_AR}};

    //LINEA DE AR
    tablaM[NT_AR][TOK_ID].cuerpo = {{TERMINAL, TOK_ID}};
    tablaM[NT_AR][TOK_CORCHETEIZQ].cuerpo = {{TERMINAL, TOK_CORCHETEIZQ}, {NO_TERMINAL, NT_TPP}};

    //LINEA DE Dp
    tablaM[NT_Dp][TOK_IGUAL].cuerpo = {{TERMINAL, TOK_IGUAL}, {TERMINAL, TOK_REFFERENCE}, {TERMINAL, TOK_ID}};
    tablaM[NT_Dp][TOK_PUNTOYCOMA].cuerpo = {{TERMINAL, TOK_e}};

    //LINEA DE Ep
    tablaM[NT_Ep][TOK_ID].cuerpo = {{TERMINAL, TOK_e}};
    tablaM[NT_Ep][TOK_ASTERISCO].cuerpo = {{TERMINAL, TOK_ASTERISCO}, {NO_TERMINAL, NT_Ep}};

    //LINEA DE F
    tablaM[NT_F][TOK_PUTS].cuerpo = {{TERMINAL, TOK_PUTS}, {NO_TERMINAL, NT_E}}; //, {TERMINAL, TOK_PUNTOYCOMA}};
    tablaM[NT_F][TOK_LLAVEDER].cuerpo = {{TERMINAL, TOK_LLAVEDER}};

    //LINEA DE E
    tablaM[NT_E][TOK_MAS].cuerpo  = {{NO_TERMINAL, NT_P}, {NO_TERMINAL, NT_E}};
    tablaM[NT_E][TOK_MENOS].cuerpo= {{NO_TERMINAL, NT_P}, {NO_TERMINAL, NT_E}};
    tablaM[NT_E][TOK_DIVISION].cuerpo={{NO_TERMINAL, NT_P}, {NO_TERMINAL, NT_E}};
    tablaM[NT_E][TOK_ASTERISCO].cuerpo={{NO_TERMINAL, NT_P}, {NO_TERMINAL, NT_E}};
    tablaM[NT_E][TOK_PARENTESISIZQ].cuerpo = {{TERMINAL, TOK_PARENTESISIZQ}, {NO_TERMINAL, NT_P}, {TERMINAL, TOK_PARENTESISDER}};
    tablaM[NT_E][TOK_PARENTESISDER].cuerpo = {{TERMINAL, TOK_PARENTESISDER}};
    tablaM[NT_E][TOK_CORCHETEDER].cuerpo = {{TERMINAL, TOK_CORCHETEDER}, {NO_TERMINAL, NT_D}};

    //LINEA DE P
    tablaM[NT_P][TOK_MAS].cuerpo  = {{TERMINAL, TOK_MAS},  {NO_TERMINAL, NT_K}};
    tablaM[NT_P][TOK_MENOS].cuerpo= {{TERMINAL, TOK_MENOS},{NO_TERMINAL, NT_K}};
    tablaM[NT_P][TOK_DIVISION].cuerpo={{TERMINAL, TOK_DIVISION},{NO_TERMINAL, NT_K}};
    tablaM[NT_P][TOK_CTE_LIT].cuerpo = {{TERMINAL, TOK_CTE_LIT}};
}


void sintactico::vanalisis_sintactico()
{
    int ip = 0;
    pila.clear();

    // $
    pila.push_back({TERMINAL, TOK_$});

    // Símbolo inicial
    if (strcmp(tokens[ip], "puts") == 0)
        pila.push_back({NO_TERMINAL, NT_F});
    else
        pila.push_back({NO_TERMINAL, NT_D});



    cout << "\nProducciones:\n";

    while (!pila.empty())
    {
        Simbolo X = pila.back();
        pila.pop_back();

        int a = estoken(tokens[ip]);

        //cout << "verificando " << X.valor << " con " << a << endl;
        if (a == -1)
        {
            cout << "Error léxico\n";
            return;
        }

        // TERMINAL
        if (X.tipo == TERMINAL)
        {
            if (X.valor == TOK_e)
                continue;

            if (X.valor == a)
            {
                ip++; // consumir token
            }
            else
            {
                cout << "Error sintáctico\n";
                return;
            }
        }
        // NO TERMINAL
        else
        {
            Produccion &p = tablaM[X.valor][a];

            if (p.cuerpo.empty())
            {
                cout << "Error sintáctico\n";
                return;
            }

            // imprimir producción
            cout << varsint[X.valor] << " -> ";
            for (auto &s : p.cuerpo)
            {
                if (s.tipo == TERMINAL)
                    cout << token[s.valor] << " ";
                else
                    cout << varsint[s.valor] << " ";
            }
            cout << endl;

            // meter producción al revés
            for (int i = (int)p.cuerpo.size() - 1; i >= 0; i--)
            {
                if (p.cuerpo[i].tipo == TERMINAL &&
                    p.cuerpo[i].valor == TOK_e)
                    continue;

                pila.push_back(p.cuerpo[i]);
            }
        }
    }

    cout << "Sintaxis correcta\n";
}




int sintactico::estoken(char x[])
{
    for (int i = 0; i < NUM_TOK; i++)
        if (strcmp(x, token[i]) == 0)
            return i;

    return -1; // error léxico
}



