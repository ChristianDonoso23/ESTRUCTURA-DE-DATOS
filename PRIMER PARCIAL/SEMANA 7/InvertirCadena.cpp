/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Ejercicios colas y pilas 
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 17 de junio de 2024
 * Fecha modificacion: viernes , 21 de junio de 2024 
 ***********************************************************************/
#include <iostream>
#include <stack>
#include <string>

int main() {
    std::stack<char> pila;
    std::string cadena, invertida;

    std::cout << "Ingresa una cadena: ";
    std::getline(std::cin, cadena);

    for (char c : cadena) {
        pila.push(c);
    }

    while (!pila.empty()) {
        invertida += pila.top();
        pila.pop();
    }

    std::cout << "Cadena invertida: " << invertida << std::endl;

    return 0;
}
