/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Declaracion de la clase 
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 20 de mayo de 2024
 * Fecha modificacion: viernes ,24 de mayo de 2024 
 ***********************************************************************/
#include <iostream>
class Frac{
private:
    int a;
    int b;
public:
    Frac():a(0),b(0){}
    void in();
    Frac operator*(const Frac &obj);
    void out();

};
