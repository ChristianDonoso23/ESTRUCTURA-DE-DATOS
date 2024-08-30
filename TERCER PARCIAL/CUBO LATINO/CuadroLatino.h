#ifndef CUADRADO_LATINO_H
#define CUADRADO_LATINO_H

#include <graphics.h>
#include <iostream>
#include <cstdlib>

class CuadradoLatino {
private:
    int n;                 // Orden del cuadrado latino
    int** cuadradoLatino;  // Matriz para el cuadrado latino
    int* numeros;          // Arreglo de números

public:
    CuadradoLatino(int orden);
    ~CuadradoLatino();

    void llenarCuadrado();
    void imprimirCuadrado();
    void generarCuadrado();
    void leerNumeros();
    static int leerEntero(const std::string& mensaje);
};

#endif // CUADRADO_LATINO_H
