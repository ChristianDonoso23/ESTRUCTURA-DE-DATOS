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
void Racional::in(){
    cout<<"Ingrese el numerador: ";
    cin>>numerador;
    do{
        cout<<"Ingrese el denominador (diferente de 0): ";
        cin>>denominador;
    }while(denominador==0);
}
Racional Racional::operator/(const Racional &obj){
    Racional fracion;
    fracion.numerador=numerador*obj.denominador;
    fracion.denominador=denominador*obj.numerador;
    return fracion;
}
void Racional::out(){
    cout<<"El resultado de la division es:"<<numerador<<"/"<<denominador<<endl;

}
