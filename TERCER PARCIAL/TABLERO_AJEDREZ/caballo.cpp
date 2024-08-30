#include "caballo.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <graphics.h>

using namespace std;

void dibujarCaballo(int x, int y, int tamanoCuadro, const char* pathImagen) {
    int margen = tamanoCuadro * 0.1;
    readimagefile(pathImagen, x + margen, y + margen, x + tamanoCuadro - margen, y + tamanoCuadro - margen);
}

bool esPosicionValida(int fila, int columna, int n) {
    return fila >= 0 && fila < n && columna >= 0 && columna < n;
}

int* inicializarMovimientosCaballo() {
    int* movimientosCaballo = (int*)malloc(16 * sizeof(int));
    
    *(movimientosCaballo + 0) = -2; *(movimientosCaballo + 1) = -1;
    *(movimientosCaballo + 2) = -1; *(movimientosCaballo + 3) = -2;
    *(movimientosCaballo + 4) = 1;  *(movimientosCaballo + 5) = -2;
    *(movimientosCaballo + 6) = 2;  *(movimientosCaballo + 7) = -1;
    *(movimientosCaballo + 8) = 2;  *(movimientosCaballo + 9) = 1;
    *(movimientosCaballo + 10) = 1; *(movimientosCaballo + 11) = 2;
    *(movimientosCaballo + 12) = -1; *(movimientosCaballo + 13) = 2;
    *(movimientosCaballo + 14) = -2; *(movimientosCaballo + 15) = 1;
    
    return movimientosCaballo;
}

void liberarMovimientosCaballo(int* movimientosCaballo) {
    free(movimientosCaballo);
}

void mostrarMovimientosCaballoRecursivo(int fila, int columna, int n, Tablero tablero, const char* pathCaballoNegro, int i, int* movimientosCaballo) {
    if (i >= 8) {
        return;
    }

    int* movimientoActual = movimientosCaballo + 2 * i;
    int nuevaFila = fila + *movimientoActual;
    int nuevaColumna = columna + *(movimientoActual + 1);

    if (esPosicionValida(nuevaFila, nuevaColumna, n)) {
        cout << "Fila: " << nuevaFila + 1 << ", Columna: " << nuevaColumna + 1 << endl;
        int x = tablero.inicioX + nuevaColumna * tablero.tamanoCuadro;
        int y = tablero.inicioY + nuevaFila * tablero.tamanoCuadro;
        dibujarCaballo(x, y, tablero.tamanoCuadro, pathCaballoNegro);
    }
    mostrarMovimientosCaballoRecursivo(fila, columna, n, tablero, pathCaballoNegro, i + 1, movimientosCaballo);
}

void dibujarTableroRecursivo(Tablero tablero, int fila, int columna) {
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

void ejecutarCaballo(int n) {

    int tamanoCuadro = (n < 7) ? 70 : 50;
    int anchoTotal = tamanoCuadro * n + 40;
    int altoTotal = tamanoCuadro * n + 40;
    closegraph();

    int gd = DETECT, gm;
    initwindow(anchoTotal, altoTotal, "Tablero de Caballo");

    int inicioX = 20;
    int inicioY = 20;

    Tablero tablero = { n, tamanoCuadro, inicioX, inicioY };
    setbkcolor(DARKGRAY);
    cleardevice();

    dibujarTableroRecursivo(tablero, 0, 0);

    dibujarNotacionColumnas(tablero, 0);
    dibujarNotacionFilas(tablero, 0);

    srand(time(nullptr));
    int filaCaballo = rand() % n;
    int columnaCaballo = rand() % n;

    const char* pathCaballoBlanco = "imagenes/CaballoBlanco1.jpg";
    const char* pathCaballoNegro = "imagenes/CaballoNegro1.jpg";

    int xCaballo = tablero.inicioX + columnaCaballo * tablero.tamanoCuadro;
    int yCaballo = tablero.inicioY + filaCaballo * tablero.tamanoCuadro;
    dibujarCaballo(xCaballo, yCaballo, tablero.tamanoCuadro, pathCaballoBlanco);

    int* movimientosCaballo = inicializarMovimientosCaballo();

    mostrarMovimientosCaballoRecursivo(filaCaballo, columnaCaballo, n, tablero, pathCaballoNegro, 0, movimientosCaballo);

    liberarMovimientosCaballo(movimientosCaballo);

    getch();
    closegraph();
}
