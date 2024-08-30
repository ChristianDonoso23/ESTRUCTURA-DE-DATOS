#include "tablero.h"
#include <graphics.h>
#include <iostream>
#include <stdio.h>

using namespace std;

void vaciarPiezas(string* piezas, int n, int indice) {
    if (indice >= n * n) return;
    piezas[indice] = "";
    vaciarPiezas(piezas, n, indice + 1);
}

void colocarPiezasNegras(string* piezas, int indice) {
    if (indice >= 8) return;
    string piezasNegras[8] = {"TorreNegra1", "CaballoNegro1", "AlfilNegro1", "ReinaNegra1", "ReyNegro1", "AlfilNegro1", "CaballoNegro1", "TorreNegra1"};
    piezas[indice] = piezasNegras[indice];
    piezas[indice + 8] = "PeonNegro1";
    colocarPiezasNegras(piezas, indice + 1);
}

void colocarPiezasBlancas(string* piezas, int indice) {
    if (indice >= 8) return;
    string piezasBlancas[8] = {"TorreBlanca1", "CaballoBlanco1", "AlfilBlanco1", "ReinaBlanca1", "ReyBlanco1", "AlfilBlanco1", "CaballoBlanco1", "TorreBlanca1"};
    piezas[indice + 48] = "PeonBlanco1";
    piezas[indice + 56] = piezasBlancas[indice];
    colocarPiezasBlancas(piezas, indice + 1);
}

void inicializarPiezasAjedrezEstandar(string* piezas, int n) {
    vaciarPiezas(piezas, n, 0);
    colocarPiezasNegras(piezas, 0);
    colocarPiezasBlancas(piezas, 0);
}

void dibujarCuadroConPieza(Tablero tablero, int fila, int columna, string* piezas) {
    if (fila >= tablero.n) return;

    int x = tablero.inicioX + columna * tablero.tamanoCuadro;
    int y = tablero.inicioY + fila * tablero.tamanoCuadro;

    int colorCuadro;
    if ((fila + columna) % 2 == 0) {
        setfillstyle(SOLID_FILL, WHITE);
        colorCuadro = WHITE;
    } else {
        setfillstyle(SOLID_FILL, BLACK);
        colorCuadro = BLACK;
    }

    bar(x, y, x + tablero.tamanoCuadro, y + tablero.tamanoCuadro);

    if (piezas != nullptr) {
        string pieza = piezas[fila * tablero.n + columna];
        if (!pieza.empty()) {
            int margen = tablero.tamanoCuadro * 0.1;
            string path = "imagenes/" + pieza + ".jpg";
            readimagefile(path.c_str(), x + margen, y + margen, x + tablero.tamanoCuadro - margen, y + tablero.tamanoCuadro - margen);
        }
    }

    if (columna < tablero.n - 1) {
        dibujarCuadroConPieza(tablero, fila, columna + 1, piezas);
    } else {
        dibujarCuadroConPieza(tablero, fila + 1, 0, piezas);
    }
}

void dibujarNotacionColumnas(Tablero tablero, int i) {
    if (i >= tablero.n) return;
    char columna[2];
    sprintf(columna, "%c", 'a' + i);
    outtextxy(tablero.inicioX + i * tablero.tamanoCuadro + tablero.tamanoCuadro / 2 - 5, 
              tablero.inicioY - tablero.tamanoCuadro / 4, columna);
    outtextxy(tablero.inicioX + i * tablero.tamanoCuadro + tablero.tamanoCuadro / 2 - 5, 
              tablero.inicioY + tablero.n * tablero.tamanoCuadro + tablero.tamanoCuadro / 4, columna);
    dibujarNotacionColumnas(tablero, i + 1);
}

void dibujarNotacionFilas(Tablero tablero, int i) {
    if (i >= tablero.n) return;

    char fila[2];
    sprintf(fila, "%d", 8 - i);
    outtextxy(tablero.inicioX - tablero.tamanoCuadro / 4, 
              tablero.inicioY + i * tablero.tamanoCuadro + tablero.tamanoCuadro / 2 - 5, fila);
    outtextxy(tablero.inicioX + tablero.n * tablero.tamanoCuadro + tablero.tamanoCuadro / 4, 
              tablero.inicioY + i * tablero.tamanoCuadro + tablero.tamanoCuadro / 2 - 5, fila);
    dibujarNotacionFilas(tablero, i + 1);
}

void obtenerTamanoVentana(int& ancho, int& alto) {
    ancho = getmaxx() + 1;
    alto = getmaxy() + 1;
}

void mostrarTableroSinPiezas() {
    int n = 8;

    int tamanoCuadro = 50;
    int anchoTotal = tamanoCuadro * n + 40;
    int altoTotal = tamanoCuadro * n + 40;

    int gd = DETECT, gm;
    initwindow(anchoTotal, altoTotal, "Tablero de Ajedrez");
    int inicioX = 20;
    int inicioY = 20;
    Tablero tablero = { n, tamanoCuadro, inicioX, inicioY };
    setbkcolor(DARKGRAY);
    cleardevice();
    dibujarCuadroConPieza(tablero, 0, 0, nullptr);
    dibujarNotacionColumnas(tablero, 0);
    dibujarNotacionFilas(tablero, 0);
    getch();
    closegraph();
}

void mostrarTableroConPiezas() {
    int n = 8;
    int tamanoCuadro = 50;
    int anchoTotal = tamanoCuadro * n + 40;
    int altoTotal = tamanoCuadro * n + 40;

    int gd = DETECT, gm;
    initwindow(anchoTotal, altoTotal, "Tablero de Ajedrez");
    int inicioX = 20;
    int inicioY = 20;
    Tablero tablero = { n, tamanoCuadro, inicioX, inicioY };

    string* piezas = new string[n * n];
    inicializarPiezasAjedrezEstandar(piezas, n);
    setbkcolor(DARKGRAY);
    cleardevice();
    dibujarCuadroConPieza(tablero, 0, 0, piezas);
    dibujarNotacionColumnas(tablero, 0);
    dibujarNotacionFilas(tablero, 0);
    getch();
    closegraph();
    delete[] piezas;
}
