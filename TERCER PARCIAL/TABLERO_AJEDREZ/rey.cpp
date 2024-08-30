#include "rey.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <graphics.h>

using namespace std;

void dibujarRey(int x, int y, int tamanoCuadro, const char* pathImagen) {
    int margen = tamanoCuadro * 0.1;
    readimagefile(pathImagen, x + margen, y + margen, x + tamanoCuadro - margen, y + tamanoCuadro - margen);
}

bool esPosicionValidaRey(int fila, int columna, int n) {
    return fila >= 0 && fila < n && columna >= 0 && columna < n;
}

int* inicializarMovimientosRey() {
    int* movimientosRey = (int*)malloc(16 * sizeof(int));
    
    *(movimientosRey + 0) = -1; *(movimientosRey + 1) = -1;  // Diagonal arriba-izquierda
    *(movimientosRey + 2) = -1; *(movimientosRey + 3) = 0;   // Arriba
    *(movimientosRey + 4) = -1; *(movimientosRey + 5) = 1;   // Diagonal arriba-derecha
    *(movimientosRey + 6) = 0;  *(movimientosRey + 7) = 1;   // Derecha
    *(movimientosRey + 8) = 1;  *(movimientosRey + 9) = 1;   // Diagonal abajo-derecha
    *(movimientosRey + 10) = 1; *(movimientosRey + 11) = 0;  // Abajo
    *(movimientosRey + 12) = 1; *(movimientosRey + 13) = -1; // Diagonal abajo-izquierda
    *(movimientosRey + 14) = 0; *(movimientosRey + 15) = -1; // Izquierda
    
    return movimientosRey;
}

void liberarMovimientosRey(int* movimientosRey) {
    free(movimientosRey);
}

void mostrarMovimientosReyRecursivo(int fila, int columna, int n, Tablero tablero, const char* pathReyNegro, int i, int* movimientosRey) {
    if (i >= 8) {  // El rey tiene 8 movimientos posibles
        return;
    }

    int* movimientoActual = movimientosRey + 2 * i;
    int nuevaFila = fila + *movimientoActual;
    int nuevaColumna = columna + *(movimientoActual + 1);

    if (esPosicionValida(nuevaFila, nuevaColumna, n)) {
        cout << "Fila: " << nuevaFila + 1 << ", Columna: " << nuevaColumna + 1 << endl;
        int x = tablero.inicioX + nuevaColumna * tablero.tamanoCuadro;
        int y = tablero.inicioY + nuevaFila * tablero.tamanoCuadro;
        dibujarRey(x, y, tablero.tamanoCuadro, pathReyNegro);
    }
    mostrarMovimientosReyRecursivo(fila, columna, n, tablero, pathReyNegro, i + 1, movimientosRey);
}

void dibujarTableroRecursivoRey(Tablero tablero, int fila, int columna) {
    if (fila >= tablero.n) {
        return;
    }

    dibujarCuadroConPieza(tablero, fila, columna, nullptr);

    if (columna + 1 < tablero.n) {
        dibujarTableroRecursivo(tablero, fila, columna + 1);
    } else {
        dibujarTableroRecursivo(tablero, fila + 1, 0);
    }
}

void ejecutarRey(int n) {

    int tamanoCuadro = (n < 7) ? 70 : 50;
    int anchoTotal = tamanoCuadro * n + 40;
    int altoTotal = tamanoCuadro * n + 40;
    closegraph();

    int gd = DETECT, gm;
    initwindow(anchoTotal, altoTotal, "Tablero de Rey");

    int inicioX = 20;
    int inicioY = 20;

    Tablero tablero = { n, tamanoCuadro, inicioX, inicioY };
    setbkcolor(DARKGRAY);
    cleardevice();

    dibujarTableroRecursivo(tablero, 0, 0);

    dibujarNotacionColumnas(tablero, 0);
    dibujarNotacionFilas(tablero, 0);

    srand(time(nullptr));
    int filaRey = rand() % n;
    int columnaRey = rand() % n;

    const char* pathReyBlanco = "imagenes/ReyBlanco1.jpg";
    const char* pathReyNegro = "imagenes/ReyNegro1.jpg";

    int xRey = tablero.inicioX + columnaRey * tablero.tamanoCuadro;
    int yRey = tablero.inicioY + filaRey * tablero.tamanoCuadro;
    dibujarRey(xRey, yRey, tablero.tamanoCuadro, pathReyBlanco);

    int* movimientosRey = inicializarMovimientosRey();

    mostrarMovimientosReyRecursivo(filaRey, columnaRey, n, tablero, pathReyNegro, 0, movimientosRey);

    liberarMovimientosRey(movimientosRey);

    getch();
    closegraph();
}
