#ifndef GRAFICO_H
#define GRAFICO_H

#include <graphics.h>
#include <sstream>
#include "Conjunto.h"

class Grafico {
public:
    void inicializarGraficos();
    template <typename T>
    void graficarConjunto(int x, int y, const char* nombre, T* elementos, int tamano);
    template <typename T>
    void graficarUnion(T* A, int tamA, T* B, int tamB);
    template <typename T>
    void graficarInterseccion(T* A, int tamA, T* B, int tamB);
    template <typename T>
    void graficarDiferencia(T* A, int tamA, T* B, int tamB, bool ab);
    template <typename T>
    void graficarComplemento(T* universo, int tamU, T* A, int tamA, bool a);
    template <typename T>
    void graficarConjuntosSeparados(T* A, int tamA, T* B, int tamB);
};

#include "Grafico.cpp"

#endif
