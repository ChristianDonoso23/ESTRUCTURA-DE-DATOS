#ifndef CONJUNTO_H
#define CONJUNTO_H

#include <iostream>
#include <string>
#include <sstream>
#include <conio.h>

template <typename T>
class Conjunto {
public:
    static T* asignarMemoria(int tamano);
    static bool existeEnConjunto(const T* conjunto, int tamano, T elemento);
    static void ingresarConjunto(T* conjunto, int tamano, char nombreConjunto, int indiceElemento = 1);
    static T* unionConjuntos(T* A, int tamA, T* B, int tamB, int& tamUnion);
    static T* interseccionConjuntos(T* A, int tamA, T* B, int tamB, int& tamInterseccion, int idxA = 0, int idxI = 0);
    static T* diferenciaAmenosB(T* A, int tamA, T* B, int tamB, int& tamDiferencia, int idxA = 0, int idxD = 0);
    static T* diferenciaBmenosA(T* B, int tamB, T* A, int tamA, int& tamDiferencia, int idxB = 0, int idxD = 0);
    static T* complementoConjunto(T* universo, int tamU, T* A, int tamA, int& tamComplemento, int idxU = 0, int idxC = 0);
};

#include "Conjunto.cpp"

#endif
