/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Ejercicios colas y pilas 
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 17 de junio de 2024
 * Fecha modificacion: viernes , 21 de junio de 2024 
 ***********************************************************************/
#include <iostream>
#include <stack>

void revertirPila(std::stack<int>& pila) {
    std::stack<int> aux1, aux2;

    while (!pila.empty()) {
        aux1.push(pila.top());
        pila.pop();
    }

    while (!aux1.empty()) {
        aux2.push(aux1.top());
        aux1.pop();
    }

    while (!aux2.empty()) {
        pila.push(aux2.top());
        aux2.pop();
    }
}

int main() {
    std::stack<int> pila;
    pila.push(1);
    pila.push(2);
    pila.push(3);
    pila.push(4);
    pila.push(5);

    std::cout << "Pila original: ";
    std::stack<int> temp = pila;
    while (!temp.empty()) {
        std::cout << temp.top() << " ";
        temp.pop();
    }
    std::cout << std::endl;

    revertirPila(pila);

    std::cout << "Pila revertida: ";
    while (!pila.empty()) {
        std::cout << pila.top() << " ";
        pila.pop();
    }
    std::cout << std::endl;

    return 0;
}
