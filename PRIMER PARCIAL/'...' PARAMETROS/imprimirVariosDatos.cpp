/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Ejercicios con ... como parametro
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 27 de mayo de 2024
 * Fecha modificacion: viernes ,31 de mayo de 2024 
 ***********************************************************************/
#include <iostream>
#include <cstdarg>

void imprimir(int count, ...) {
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i) {
        switch (va_arg(args, int)) {
            case 1: // entero
                std::cout << va_arg(args, int) << " ";
                break;
            case 2: // double
                std::cout << va_arg(args, double) << " ";
                break;
            case 3: // const char*
                std::cout << va_arg(args, const char*) << " ";
                break;
        }
    }
    va_end(args);
    std::cout << std::endl;
}

int main() {
    imprimir(5, 1, 10, 2, 3.14, 3, "Hola", 1, 42, 3, "Mundo");
    return 0;
}
