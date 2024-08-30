#ifndef ALFIL_H
#define ALFIL_H

#include "tablero.h"

struct MovimientoAlfil {
    int fila;
    int columna;
    char accion[10];
};

void dibujarAlfil(int x, int y, int tamanoCuadro, const char* pathImagen);
bool esPosicionValidaAlfil(int fila, int columna, int n);
void mostrarMovimientosAlfilRecursivo(int fila, int columna, int n, Tablero tablero, const char* pathAlfilNegro, int i);
void dibujarTableroRecursivoAlfil(Tablero tablero, int fila, int columna);
void ejecutarAlfil(int n);

#endif // ALFIL_H
