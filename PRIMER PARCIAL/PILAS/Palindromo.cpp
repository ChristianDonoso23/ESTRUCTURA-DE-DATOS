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

bool esPalindromo(const std::string& cadena) {
    std::stack<char> pila;
    for (char c : cadena) {
        pila.push(c);
    }

    for (char c : cadena) {
        if (c != pila.top()) {
            return false;
        }
        pila.pop();
    }

    return true;
}

int main() {
    std::string cadena;

    std::cout << "Ingresa una cadena: ";
    std::getline(std::cin, cadena);

    if (esPalindromo(cadena)) {
        std::cout << "La cadena es un palíndromo." << std::endl;
    } else {
        std::cout << "La cadena no es un palíndromo." << std::endl;
    }

    return 0;
}
