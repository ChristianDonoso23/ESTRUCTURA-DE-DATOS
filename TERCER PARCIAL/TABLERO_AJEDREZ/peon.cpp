#include "peon.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <graphics.h>

using namespace std;

void dibujarPeon(int x, int y, int tamanoCuadro, const char* pathImagen) {
    int margen = tamanoCuadro * 0.1;
    readimagefile(pathImagen, x + margen, y + margen, x + tamanoCuadro - margen, y + tamanoCuadro - margen);
}

bool esPosicionValidaPeon(int fila, int columna, int n) {
    return fila >= 0 && fila < n && columna >= 0 && columna < n;
}

void mostrarMovimientosPeon(int fila, int columna, int n, Tablero tablero, const char* pathPeonNegro) {
    int direccionAdelante = -1;  // El peón blanco se mueve hacia arriba
    int filaInicial = n - 2;

    // Movimiento hacia adelante
    int nuevaFila = fila + direccionAdelante;
    if (esPosicionValidaPeon(nuevaFila, columna, n)) {
        cout << "Fila: " << nuevaFila + 1 << ", Columna: " << columna + 1 << endl;
        int x = tablero.inicioX + columna * tablero.tamanoCuadro;
        int y = tablero.inicioY + nuevaFila * tablero.tamanoCuadro;
        dibujarPeon(x, y, tablero.tamanoCuadro, pathPeonNegro);
    }

    // Movimiento de dos casillas desde la posición inicial
    if (fila == filaInicial) {
        int dosCasillasAdelante = fila + 2 * direccionAdelante;
        if (esPosicionValidaPeon(dosCasillasAdelante, columna, n)) {
            cout << "Fila: " << dosCasillasAdelante + 1 << ", Columna: " << columna + 1 << endl;
            int x = tablero.inicioX + columna * tablero.tamanoCuadro;
            int y = tablero.inicioY + dosCasillasAdelante * tablero.tamanoCuadro;
            dibujarPeon(x, y, tablero.tamanoCuadro, pathPeonNegro);
        }
    }

    // Captura diagonal izquierda
    int nuevaColumnaIzquierda = columna - 1;
    if (esPosicionValidaPeon(nuevaFila, nuevaColumnaIzquierda, n)) {
        cout << "Fila: " << nuevaFila + 1 << ", Columna: " << nuevaColumnaIzquierda + 1 << endl;
        int x = tablero.inicioX + nuevaColumnaIzquierda * tablero.tamanoCuadro;
        int y = tablero.inicioY + nuevaFila * tablero.tamanoCuadro;
        dibujarPeon(x, y, tablero.tamanoCuadro, pathPeonNegro);
    }

    // Captura diagonal derecha
    int nuevaColumnaDerecha = columna + 1;
    if (esPosicionValidaPeon(nuevaFila, nuevaColumnaDerecha, n)) {
        cout << "Fila: " << nuevaFila + 1 << ", Columna: " << nuevaColumnaDerecha + 1 << endl;
        int x = tablero.inicioX + nuevaColumnaDerecha * tablero.tamanoCuadro;
        int y = tablero.inicioY + nuevaFila * tablero.tamanoCuadro;
        dibujarPeon(x, y, tablero.tamanoCuadro, pathPeonNegro);
    }
}


void dibujarTableroRecursivoPeon(Tablero tablero, int fila, int columna) {
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

void ejecutarPeon(int n) {

    int tamanoCuadro = (n < 7) ? 70 : 50;
    int anchoTotal = tamanoCuadro * n + 40;
    int altoTotal = tamanoCuadro * n + 40;
    closegraph();

    int gd = DETECT, gm;
    initwindow(anchoTotal, altoTotal, "Tablero de Peón");

    int inicioX = 20;
    int inicioY = 20;

    Tablero tablero = { n, tamanoCuadro, inicioX, inicioY };
    setbkcolor(DARKGRAY);
    cleardevice();

    dibujarTableroRecursivo(tablero, 0, 0);

    dibujarNotacionColumnas(tablero, 0);
    dibujarNotacionFilas(tablero, 0);

    srand(time(nullptr));
    int filaPeon = rand() % n;
    int columnaPeon = rand() % n;

    const char* pathPeonBlanco = "imagenes/PeonBlanco1.jpg";
    const char* pathPeonNegro = "imagenes/PeonNegro1.jpg";

    int xPeon = tablero.inicioX + columnaPeon * tablero.tamanoCuadro;
    int yPeon = tablero.inicioY + filaPeon * tablero.tamanoCuadro;
    dibujarPeon(xPeon, yPeon, tablero.tamanoCuadro, pathPeonBlanco);

    mostrarMovimientosPeon(filaPeon, columnaPeon, n, tablero, pathPeonNegro);

    getch();
    closegraph();
}
