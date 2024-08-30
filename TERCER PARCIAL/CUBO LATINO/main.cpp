#include <iostream>
#include "CuadroLatino.cpp"

int main() {
    int n;

    // Solicitar el orden del cuadrado latino
    while (true) {
        n = CuadradoLatino::leerEntero("Ingrese el orden del cuadrado latino (n): ");

        // Verificar que n sea mayor o igual a 3
        if (n >= 3) {
            break; // Salir del bucle si la condición es cumplida
        } else {
            std::cout << "El orden debe ser mayor o igual a 3. Intentelo de nuevo." << std::endl;
        }
    }

    CuadradoLatino cuadrado(n);
    cuadrado.generarCuadrado();

    return 0;
}
