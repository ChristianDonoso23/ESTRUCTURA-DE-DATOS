/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Declaracion de la clase 
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 20 de mayo de 2024
 * Fecha modificacion: viernes ,24 de mayo de 2024 
 ***********************************************************************/
#include <iostream>
#include "Frac.h"
using namespace std;
int main(){
    Frac F1,F2,result;
    system("cls");
    cout<<"Ingrese la primera fraccion: "<<endl;
    F1.in();

    cout<<"Ingrese la segunda fraccion: "<<endl;
    F2.in();
    result = F1*F2;
    result.out();

    return 0;

}
