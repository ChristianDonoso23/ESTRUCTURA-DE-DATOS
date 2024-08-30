/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Ejercicios colas y pilas 
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 17 de junio de 2024
 * Fecha modificacion: viernes , 21 de junio de 2024 
 ***********************************************************************/
#include <iostream>
#include <queue>

int main() {
    std::queue<int> cola;
    
    if (cola.empty()) {
        std::cout << "La cola está vacía." << std::endl;
    } else {
        std::cout << "La cola no está vacía." << std::endl;
    }

    cola.push(1);
    
    if (cola.empty()) {
        std::cout << "La cola está vacía." << std::endl;
    } else {
        std::cout << "La cola no está vacía." << std::endl;
    }

    return 0;
}
