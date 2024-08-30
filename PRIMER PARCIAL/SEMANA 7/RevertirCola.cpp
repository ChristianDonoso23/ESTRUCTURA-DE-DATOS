/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Ejercicios colas y pilas 
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 17 de junio de 2024
 * Fecha modificacion: viernes , 21 de junio de 2024 
 ***********************************************************************/
#include <iostream>
#include <queue>
#include <stack>

void revertirCola(std::queue<int>& cola) {
    std::stack<int> pila;
    while (!cola.empty()) {
        pila.push(cola.front());
        cola.pop();
    }
    while (!pila.empty()) {
        cola.push(pila.top());
        pila.pop();
    }
}

int main() {
    std::queue<int> cola;
    cola.push(1);
    cola.push(2);
    cola.push(3);
    
    revertirCola(cola);
    
    std::cout << "Cola después de revertir: ";
    while (!cola.empty()) {
        std::cout << cola.front() << " ";
        cola.pop();
    }
    std::cout << std::endl;

    return 0;
}
