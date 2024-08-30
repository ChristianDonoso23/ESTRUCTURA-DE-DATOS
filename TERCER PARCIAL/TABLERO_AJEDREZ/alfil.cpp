#include "alfil.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <graphics.h>

using namespace std;

void dibujarAlfil(int x, int y, int tamanoCuadro, const char* pathImagen) {
    int margen = tamanoCuadro * 0.1;
    readimagefile(pathImagen, x + margen, y + margen, x + tamanoCuadro - margen, y + tamanoCuadro - margen);
}

bool esPosicionValidaAlfil(int fila, int columna, int n) {
    return fila >= 0 && fila < n && columna >= 0 && columna < n;
}

void mostrarMovimientosAlfilRecursivo(int fila, int columna, int n, Tablero tablero, const char* pathAlfilNegro, int i) {
    if (i >= 4) {
        return;
    }

    // Asignación dinámica de las direcciones del alfil usando punteros
    int* direcciones = (int*)malloc(8 * sizeof(int));

    // Diagonal arriba-izquierda
    *(direcciones + 0) = -1;
    *(direcciones + 1) = -1;

    // Diagonal arriba-derecha
    *(direcciones + 2) = -1;
    *(direcciones + 3) = 1;

    // Diagonal abajo-izquierda
    *(direcciones + 4) = 1;
    *(direcciones + 5) = -1;

    // Diagonal abajo-derecha
    *(direcciones + 6) = 1;
    *(direcciones + 7) = 1;

    int* direccionActual = direcciones + (i * 2);
    int nuevaFila = fila + *direccionActual;
    int nuevaColumna = columna + *(direccionActual + 1);

    while (esPosicionValida(nuevaFila, nuevaColumna, n)) {
        cout << "Fila: " << nuevaFila + 1 << ", Columna: " << nuevaColumna + 1 << endl;
        int x = tablero.inicioX + nuevaColumna * tablero.tamanoCuadro;
        int y = tablero.inicioY + nuevaFila * tablero.tamanoCuadro;
        dibujarAlfil(x, y, tablero.tamanoCuadro, pathAlfilNegro);
        nuevaFila += *direccionActual;
        nuevaColumna += *(direccionActual + 1);
    }

    free(direcciones);

    mostrarMovimientosAlfilRecursivo(fila, columna, n, tablero, pathAlfilNegro, i + 1);
}


void dibujarTableroRecursivoAlfil(Tablero tablero, int fila, int columna) {
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

void ejecutarAlfil(int n) {

    int tamanoCuadro = (n < 7) ? 70 : 50;
    int anchoTotal = tamanoCuadro * n + 40;
    int altoTotal = tamanoCuadro * n + 40;
    closegraph();

    int gd = DETECT, gm;
    initwindow(anchoTotal, altoTotal, "Tablero de Alfil");

    int inicioX = 20;
    int inicioY = 20;

    Tablero tablero = { n, tamanoCuadro, inicioX, inicioY };
    setbkcolor(DARKGRAY);
    cleardevice();

    dibujarTableroRecursivo(tablero, 0, 0);

    dibujarNotacionColumnas(tablero, 0);
    dibujarNotacionFilas(tablero, 0);

    srand(time(nullptr));
    int filaAlfil = rand() % n;
    int columnaAlfil = rand() % n;

    const char* pathAlfilBlanco = "imagenes/AlfilBlanco1.jpg";
    const char* pathAlfilNegro = "imagenes/AlfilNegro1.jpg";

    int xAlfil = tablero.inicioX + columnaAlfil * tablero.tamanoCuadro;
    int yAlfil = tablero.inicioY + filaAlfil * tablero.tamanoCuadro;
    dibujarAlfil(xAlfil, yAlfil, tablero.tamanoCuadro, pathAlfilBlanco);

    mostrarMovimientosAlfilRecursivo(filaAlfil, columnaAlfil, n, tablero, pathAlfilNegro, 0);

    getch();
    closegraph();
}
