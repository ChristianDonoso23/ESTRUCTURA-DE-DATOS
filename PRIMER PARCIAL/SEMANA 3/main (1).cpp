/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Declaracion de la clase 
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 20 de mayo de 2024
 * Fecha modificacion: viernes ,24 de mayo de 2024 
 ***********************************************************************/
#include <iostream>
#include "Persona.cpp"

int main(int argc, char **argv) {
    Persona pedro("Pedro", 25,72.50);
    Persona shirley("Shirley", 21,68.30);
    Persona manuel("Manuel", 20,40.24);

	cout<<"\n---Sobrecarga del operador relacional (>)---\n";
    cout << pedro.getNombre()
        << " (" << pedro.getEdad() << ") "
        << " es " << (pedro > shirley ? "mayor" : "menor") << " a " << shirley.getNombre()
        << " (" << shirley.getEdad() << ") "
        << endl;
    system("pause");
    return 0;
}


