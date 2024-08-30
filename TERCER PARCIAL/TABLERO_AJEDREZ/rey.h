#ifndef REY_H
#define REY_H

void dibujarRey(int x, int y, int tamanoCuadro, const char* pathImagen);
bool esPosicionValida(int fila, int columna, int n);
int* inicializarMovimientosRey();
void liberarMovimientosRey(int* movimientosRey);
void mostrarMovimientosReyRecursivo(int fila, int columna, int n, Tablero tablero, const char* pathReyNegro, int i, int* movimientosRey);
void dibujarTableroRecursivo(Tablero tablero, int fila, int columna);
void ejecutarRey(int n);

#endif // REY_H
