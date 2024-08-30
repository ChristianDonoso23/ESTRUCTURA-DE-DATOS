/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Ejercicios colas y pilas 
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 17 de junio de 2024
 * Fecha modificacion: viernes , 21 de junio de 2024 
 ***********************************************************************/
#include <iostream>
#include <queue>

int contarVocales(std::queue<char>& cola) {
    int conteo = 0;
    std::queue<char> temp = cola;
    while (!temp.empty()) {
        char c = temp.front();
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            conteo++;
        }
        temp.pop();
    }
    return conteo;
}

int main() {
    std::queue<char> cola;
    cola.push('h');
    cola.push('e');
    cola.push('l');
    cola.push('l');
    cola.push('o');

    int numVocales = contarVocales(cola);
    std::cout << "El número de vocales en la cola es: " << numVocales << std::endl;

    return 0;
}
