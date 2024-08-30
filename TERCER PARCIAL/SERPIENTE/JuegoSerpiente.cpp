#include "JuegoSerpiente.h"
#include <graphics.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

#define ANCHO_PANTALLA 640  // Ancho de la ventana gráfica
#define ALTO_PANTALLA 480   // Alto de la ventana gráfica
#define ANCHO 32            // Número de celdas horizontales (ajustado al nuevo tamaño)
#define ALTO 24             // Número de celdas verticales (ajustado al nuevo tamaño)
#define TAMANO_CELDA 20     // Tamaño de cada celda en píxeles, ahora más grande

JuegoSerpiente::JuegoSerpiente(ModoJuego modo) : juegoTerminado(false), direccion(PARADO), modoJuego(modo) {
    Configurar();
}

void JuegoSerpiente::Configurar() {
    initwindow(ANCHO_PANTALLA, ALTO_PANTALLA, "Juego de la Serpiente");

    setbkcolor(CYAN);
    cleardevice();

    serpiente.AgregarFrente(ANCHO / 2, ALTO / 2);

    srand(time(0));

    if (modoJuego == DIFICIL) {
        for (int i = 0; i < 10; i++) {
            int ox = rand() % (ANCHO - 2);
            int oy = rand() % (ALTO - 2);
            bool horizontal = rand() % 2 == 0;
            for (int j = 0; j < 3; j++) {
                if (horizontal) {
                    obstaculos.AgregarObstaculo(ox + j, oy);
                } else {
                    obstaculos.AgregarObstaculo(ox, oy + j);
                }
            }
        }
    }
    do {
        comida.x = rand() % ANCHO;
        comida.y = rand() % ALTO;
    } while (esPosicionOcupadaPorObstaculo(comida.x, comida.y));
}

bool JuegoSerpiente::esPosicionOcupadaPorObstaculo(int x, int y) const {
    NodoObstaculo* temp = obstaculos.ObtenerCabeza();
    while (temp) {
        if (temp->posicion.x == x && temp->posicion.y == y) {
            return true;
        }
        temp = temp->siguiente;
    }
    return false;
}

void JuegoSerpiente::Dibujar() {
    cleardevice();
    rectangle(0, 0, ANCHO * TAMANO_CELDA, ALTO * TAMANO_CELDA);
    if (modoJuego == DIFICIL) {
        NodoObstaculo* temp = obstaculos.ObtenerCabeza();
        setfillstyle(SOLID_FILL, MAGENTA);
        while (temp) {
            bar(temp->posicion.x * TAMANO_CELDA, temp->posicion.y * TAMANO_CELDA, (temp->posicion.x + 1) * TAMANO_CELDA, (temp->posicion.y + 1) * TAMANO_CELDA);
            temp = temp->siguiente;
        }
    }

    setfillstyle(SOLID_FILL, RED);
    fillellipse(comida.x * TAMANO_CELDA + TAMANO_CELDA / 2, comida.y * TAMANO_CELDA + TAMANO_CELDA / 2, TAMANO_CELDA / 2, TAMANO_CELDA / 2); // Comida más grande

    NodoSerpiente* temp = serpiente.ObtenerCabeza();
    setfillstyle(SOLID_FILL, GREEN);
    while (temp) {
        fillellipse(temp->posicion.x * TAMANO_CELDA + TAMANO_CELDA / 2, temp->posicion.y * TAMANO_CELDA + TAMANO_CELDA / 2, TAMANO_CELDA / 2, TAMANO_CELDA / 2);
        temp = temp->siguiente;
    }

    delay(100);
}

void JuegoSerpiente::CapturarEntrada() {
    if (kbhit()) {
        switch (getch()) {
        case 'a':
            if (direccion != DERECHA) direccion = IZQUIERDA;
            break;
        case 'd':
            if (direccion != IZQUIERDA) direccion = DERECHA;
            break;
        case 'w':
            if (direccion != ABAJO) direccion = ARRIBA;
            break;
        case 's':
            if (direccion != ARRIBA) direccion = ABAJO;
            break;
        case 'x':
            juegoTerminado = true;
            break;
        }
    }
}

void JuegoSerpiente::Logica() {
    if (serpiente.ObtenerCabeza() == nullptr) return;

    Posicion nuevaCabeza = serpiente.ObtenerCabeza()->posicion;

    switch (direccion) {
        case IZQUIERDA:  nuevaCabeza.x -= 1; break;
        case DERECHA: nuevaCabeza.x += 1; break;
        case ARRIBA:    nuevaCabeza.y -= 1; break;
        case ABAJO:  nuevaCabeza.y += 1; break;
        default:    break;
    }

    if (modoJuego == FACIL) {
        if (nuevaCabeza.x >= ANCHO) nuevaCabeza.x = 0;
        else if (nuevaCabeza.x < 0) nuevaCabeza.x = ANCHO - 1;
        if (nuevaCabeza.y >= ALTO) nuevaCabeza.y = 0;
        else if (nuevaCabeza.y < 0) nuevaCabeza.y = ALTO - 1;
    } else if (modoJuego == MEDIO || modoJuego == DIFICIL) {
        if (nuevaCabeza.x >= ANCHO || nuevaCabeza.x < 0 || nuevaCabeza.y >= ALTO || nuevaCabeza.y < 0) {
            juegoTerminado = true;
            return;
        }
    }

    if (modoJuego == DIFICIL) {
        NodoObstaculo* temp = obstaculos.ObtenerCabeza();
        while (temp) {
            if (temp->posicion.x == nuevaCabeza.x && temp->posicion.y == nuevaCabeza.y) {
                juegoTerminado = true;
                return;
            }
            temp = temp->siguiente;
        }
    }

    NodoSerpiente* temp = serpiente.ObtenerCabeza();
    while (temp) {
        if (temp->posicion.x == nuevaCabeza.x && temp->posicion.y == nuevaCabeza.y) {
            if (temp != serpiente.ObtenerCabeza()) {
                juegoTerminado = true;
                return;
            }
        }
        temp = temp->siguiente;
    }

    serpiente.AgregarFrente(nuevaCabeza.x, nuevaCabeza.y);

    if (nuevaCabeza.x == comida.x && nuevaCabeza.y == comida.y) {
        do {
            comida.x = rand() % ANCHO;
            comida.y = rand() % ALTO;
        } while (esPosicionOcupadaPorObstaculo(comida.x, comida.y));
    } else {
        serpiente.EliminarCola();
    }
}

void JuegoSerpiente::Limpiar() {
    closegraph();
}

void JuegoSerpiente::Ejecutar() {
    juegoTerminado = false;
    while (!juegoTerminado) {
        Dibujar();
        CapturarEntrada();
        Logica();
    }
    Limpiar();
}
