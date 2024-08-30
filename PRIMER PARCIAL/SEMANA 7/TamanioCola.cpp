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
    cola.push(1);
    cola.push(2);
    cola.push(3);
    
    std::cout << "El tamaño de la cola es: " << cola.size() << std::endl;

    return 0;
}
