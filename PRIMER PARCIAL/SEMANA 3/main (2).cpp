/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Declaracion de la clase 
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 20 de mayo de 2024
 * Fecha modificacion: viernes ,24 de mayo de 2024 
 ***********************************************************************/
#include <iostream>
#include "Racional.h"
using namespace std;

int main()
{
    Racional fraccion1, fraccion2, resultado;
    system("cls");
    cout<<"Ingrese la primera fraccion"<<endl;
    fraccion1.in();
    cout<<"Ingrese la segunda fraccion"<<endl;
    fraccion2.in();
    resultado = fraccion1/fraccion2;
    resultado.out();
    return 0;
}
