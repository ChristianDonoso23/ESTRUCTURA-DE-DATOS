#include "Juego.h"
#include <conio.h>
#include <windows.h>
#include <iostream>

void Juego::jugarLaberinto(Laberinto* laberinto, int ancho, int alto) {
    int jugadorX = 1, jugadorY = 1;
    char tecla;

    // La salida siempre estará en la esquina inferior derecha
    int salidaX = ancho - 4;
    int salidaY = alto - 2;

    while (true) {
        laberinto->dibujar(jugadorX, jugadorY, salidaX, salidaY);
        tecla = _getch(); // Esperar la tecla de movimiento

        if (tecla == 13) { // Si se presiona Enter
            break; // Volver al menú principal
        }

        if (laberinto->moverJugador(jugadorX, jugadorY, tecla, salidaX, salidaY)) {
            cout << "¡Has llegado a la salida! ¡Felicidades!" << endl;
            Sleep(2000); // Pausa de 2 segundos antes de volver al menú
            break;
        }

        // Salir del juego si se presiona 'q'
        if (tecla == 'q') break;

        Sleep(100); // Retrasar un poco el ciclo
    }
}
