#include "torre.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <graphics.h>

using namespace std;

void dibujarTorre(int x, int y, int tamanoCuadro, const char* pathImagen) {
    int margen = tamanoCuadro * 0.1;
    readimagefile(pathImagen, x + margen, y + margen, x + tamanoCuadro - margen, y + tamanoCuadro - margen);
}

bool esPosicionValidaTorre(int fila, int columna, int n) {
    return fila >= 0 && fila < n && columna >= 0 && columna < n;
}

void mostrarMovimientosTorreRecursivo(int fila, int columna, int n, Tablero tablero, const char* pathTorreNegra, int i) {
    if (i >= 4) {
        return;
    }

    int* direcciones = (int*)malloc(8 * sizeof(int));

    // Direcciones: arriba, abajo, izquierda, derecha
    *(direcciones + 0) = -1;  // Arriba
    *(direcciones + 1) = 0;

    *(direcciones + 2) = 1;   // Abajo
    *(direcciones + 3) = 0;

    *(direcciones + 4) = 0;   // Izquierda
    *(direcciones + 5) = -1;

    *(direcciones + 6) = 0;   // Derecha
    *(direcciones + 7) = 1;

    int* direccionActual = direcciones + (i * 2);
    int nuevaFila = fila + *direccionActual;
    int nuevaColumna = columna + *(direccionActual + 1);

    while (esPosicionValidaTorre(nuevaFila, nuevaColumna, n)) {
        cout << "Fila: " << nuevaFila + 1 << ", Columna: " << nuevaColumna + 1 << endl;
        int x = tablero.inicioX + nuevaColumna * tablero.tamanoCuadro;
        int y = tablero.inicioY + nuevaFila * tablero.tamanoCuadro;
        dibujarTorre(x, y, tablero.tamanoCuadro, pathTorreNegra);
        nuevaFila += *direccionActual;
        nuevaColumna += *(direccionActual + 1);
    }

    free(direcciones);

    mostrarMovimientosTorreRecursivo(fila, columna, n, tablero, pathTorreNegra, i + 1);
}

void dibujarTableroRecursivoTorre(Tablero tablero, int fila, int columna) {
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

void ejecutarTorre(int n) {

    int tamanoCuadro = (n < 7) ? 70 : 50;
    int anchoTotal = tamanoCuadro * n + 40;
    int altoTotal = tamanoCuadro * n + 40;
    closegraph();

    int gd = DETECT, gm;
    initwindow(anchoTotal, altoTotal, "Tablero de Torre");

    int inicioX = 20;
    int inicioY = 20;

    Tablero tablero = { n, tamanoCuadro, inicioX, inicioY };
    setbkcolor(DARKGRAY);
    cleardevice();

    dibujarTableroRecursivo(tablero, 0, 0);

    dibujarNotacionColumnas(tablero, 0);
    dibujarNotacionFilas(tablero, 0);

    srand(time(nullptr));
    int filaTorre = rand() % n;
    int columnaTorre = rand() % n;

    const char* pathTorreBlanca = "imagenes/TorreBlanca1.jpg";
    const char* pathTorreNegra = "imagenes/TorreNegra1.jpg";

    int xTorre = tablero.inicioX + columnaTorre * tablero.tamanoCuadro;
    int yTorre = tablero.inicioY + filaTorre * tablero.tamanoCuadro;
    dibujarTorre(xTorre, yTorre, tablero.tamanoCuadro, pathTorreBlanca);

    mostrarMovimientosTorreRecursivo(filaTorre, columnaTorre, n, tablero, pathTorreNegra, 0);

    getch();
    closegraph();
}
