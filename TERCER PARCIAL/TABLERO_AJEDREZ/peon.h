// peon.h

#ifndef PEON_H
#define PEON_H

void dibujarPeon(int x, int y, int tamanoCuadro, const char* pathImagen);
bool esPosicionValidaPeon(int fila, int columna, int n);
void mostrarMovimientosPeon(int fila, int columna, int n, Tablero tablero, const char* pathPeonNegro);
void dibujarTableroRecursivoPeon(Tablero tablero, int fila, int columna);
void ejecutarPeon(int n);

#endif // PEON_H
