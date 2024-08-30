/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Ejercicios colas y pilas 
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 17 de junio de 2024
 * Fecha modificacion: viernes , 21 de junio de 2024 
 ***********************************************************************/
#include <iostream>
#include <stack>

bool buscarElemento(std::stack<int>& pila, int elemento) {
    std::stack<int> temp;
    bool encontrado = false;

    while (!pila.empty()) {
        if (pila.top() == elemento) {
            encontrado = true;
        }
        temp.push(pila.top());
        pila.pop();
    }

    while (!temp.empty()) {
        pila.push(temp.top());
        temp.pop();
    }

    return encontrado;
}

int main() {
    std::stack<int> pila;
    pila.push(1);
    pila.push(2);
    pila.push(3);
    pila.push(4);
    pila.push(5);

    int elemento;
    std::cout << "Ingresa el elemento a buscar: ";
    std::cin >> elemento;

    if (buscarElemento(pila, elemento)) {
        std::cout << "Elemento encontrado en la pila." << std::endl;
    } else {
        std::cout << "Elemento no encontrado en la pila." << std::endl;
    }

    return 0;
}
