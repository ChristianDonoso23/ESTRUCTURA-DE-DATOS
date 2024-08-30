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
