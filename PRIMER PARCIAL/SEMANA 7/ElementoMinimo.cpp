/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Ejercicios colas y pilas 
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 17 de junio de 2024
 * Fecha modificacion: viernes , 21 de junio de 2024 
 ***********************************************************************/
#include <iostream>
#include <stack>
#include <climits>

class MinStack {
private:
    std::stack<int> pila;
    std::stack<int> minPila;

public:
    void push(int x) {
        pila.push(x);
        if (minPila.empty() || x <= minPila.top()) {
            minPila.push(x);
        }
    }

    void pop() {
        if (pila.top() == minPila.top()) {
            minPila.pop();
        }
        pila.pop();
    }

    int top() {
        return pila.top();
    }

    int getMin() {
        return minPila.top();
    }
};

int main() {
    MinStack minStack;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    std::cout << "El elemento mínimo es: " << minStack.getMin() << std::endl;
    minStack.pop();
    std::cout << "El elemento en la cima es: " << minStack.top() << std::endl;
    std::cout << "El elemento mínimo es: " << minStack.getMin() << std::endl;

    return 0;
}
