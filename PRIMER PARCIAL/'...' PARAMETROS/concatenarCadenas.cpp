/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Ejercicios con ... como parametro
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 27 de mayo de 2024
 * Fecha modificacion: viernes ,31 de mayo de 2024 
 ***********************************************************************/
#include <iostream>
#include <cstdarg>
#include <cstring>

void concatenar(char* resultado, int count, ...) {
    va_list args;
    va_start(args, count);
    resultado[0] = '\0';  // Iniciar la cadena vacía
    for (int i = 0; i < count; ++i) {
        strcat(resultado, va_arg(args, const char*));
    }
    va_end(args);
}

int main() {
    char resultado[100];
    concatenar(resultado, 3, "Hola, ", "¿cómo ", "estás?");
    std::cout << "Concatenación: " << resultado << std::endl;
    return 0;
}
