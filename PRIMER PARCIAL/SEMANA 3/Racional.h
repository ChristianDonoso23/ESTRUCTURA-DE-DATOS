/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Declaracion de la clase 
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 20 de mayo de 2024
 * Fecha modificacion: viernes ,24 de mayo de 2024 
 ***********************************************************************/
#include <iostream>
class Racional{
private:
    int numerador;
    int denominador;
public:
    Racional():numerador(0),denominador(1){}
    void in();
    Racional operator/(const Racional &obj);
    void out();
};
