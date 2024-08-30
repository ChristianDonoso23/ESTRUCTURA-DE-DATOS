/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Ejercicios con ... como parametro
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 27 de mayo de 2024
 * Fecha modificacion: viernes ,31 de mayo de 2024 
 ***********************************************************************/
#include <iostream>
#include <cstdarg>

int suma(int count, ...) {
    va_list args;
    va_start(args, count);
    int total = 0;
    for (int i = 0; i < count; ++i) {
        total += va_arg(args, int);
    }
    va_end(args);
    return total;
}

int main() {
    std::cout << "Suma: " << suma(5, 1, 2, 3, 4, 5) << std::endl;
    return 0;
}
