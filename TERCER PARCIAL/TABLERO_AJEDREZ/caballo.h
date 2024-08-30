#ifndef CABALLO_H
#define CABALLO_H

#include "tablero.h"

struct MovimientoCaballo {
    int fila;
    int columna;
    char accion[10];
};

void dibujarCaballo(int x, int y, int tamanoCuadro, const char* pathImagen);
bool esPosicionValida(int fila, int columna, int n);
int* inicializarMovimientosCaballo();
void liberarMovimientosCaballo(int* movimientosCaballo);
void mostrarMovimientosCaballoRecursivo(int fila, int columna, int n, Tablero tablero, const char* pathCaballoNegro, int i, int* movimientosCaballo);
void dibujarTableroRecursivo(Tablero tablero, int fila, int columna);
void ejecutarCaballo(int n);

#endif // CABALLO_H
