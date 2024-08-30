#ifndef TORRE_H
#define TORRE_H

#include "tablero.h"

struct MovimientoTorre {
    int fila;
    int columna;
    char accion[10];
};

void dibujarTorre(int x, int y, int tamanoCuadro, const char* pathImagen);
bool esPosicionValidaTorre(int fila, int columna, int n);
void mostrarMovimientosTorreRecursivo(int fila, int columna, int n, Tablero tablero, const char* pathTorreNegra, int i);
void dibujarTableroRecursivoTorre(Tablero tablero, int fila, int columna);
void ejecutarTorre(int n);

#endif // TORRE_H
