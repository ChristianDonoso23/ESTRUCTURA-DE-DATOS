/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Ejercicios con ... como parametro
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 27 de mayo de 2024
 * Fecha modificacion: viernes ,31 de mayo de 2024 
 ***********************************************************************/
#include <iostream>
#include <cstdarg>

double promedio(int count, ...) {
    va_list args;
    va_start(args, count);
    double total = 0.0;
    for (int i = 0; i < count; ++i) {
        total += va_arg(args, double);
    }
    va_end(args);
    return (count > 0) ? total / count : 0.0;
}

int main() {
    std::cout << "Promedio: " << promedio(4, 1.5, 2.5, 3.5, 4.5) << std::endl;
    return 0;
}
