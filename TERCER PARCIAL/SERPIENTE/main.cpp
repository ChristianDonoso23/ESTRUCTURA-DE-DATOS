#include <iostream>
#include <conio.h>
#include "JuegoSerpiente.cpp"

using namespace std;

enum OpcionesMenu { OPCION_FACIL = 0, OPCION_MEDIA, OPCION_DIFICIL, OPCION_SALIR, NUM_OPCIONES };

void mostrarMenu(int seleccionActual) {
    system("cls");  // Limpia la pantalla
    cout << "Selecciona el modo de juego usando las flechas y presiona Enter:" << endl;
    cout << (seleccionActual == OPCION_FACIL ? "> " : "  ") << "Facil" << endl;
    cout << (seleccionActual == OPCION_MEDIA ? "> " : "  ") << "Medio" << endl;
    cout << (seleccionActual == OPCION_DIFICIL ? "> " : "  ") << "Dificil" << endl;
    cout << (seleccionActual == OPCION_SALIR ? "> " : "  ") << "Salir" << endl;
}

int main() {
    int seleccionActual;
    int tecla;
    while (true) {
        seleccionActual = OPCION_FACIL;
        while (true) {
            mostrarMenu(seleccionActual);
            tecla = _getch();
            if (tecla == 224) {
                tecla = _getch();
                if (tecla == 72) { 
                    seleccionActual = (seleccionActual - 1 + NUM_OPCIONES) % NUM_OPCIONES;
                } else if (tecla == 80) {
                    seleccionActual = (seleccionActual + 1) % NUM_OPCIONES;
                }
            } else if (tecla == 13) {
                break;
            }
        }

        if (seleccionActual == OPCION_SALIR) {
            cout << "Saliendo del juego..." << endl;
            break;
        }

        ModoJuego modoSeleccionado;

        switch (seleccionActual) {
            case OPCION_FACIL:
                modoSeleccionado = FACIL;
                break;
            case OPCION_MEDIA:
                modoSeleccionado = MEDIO;
                break;
            case OPCION_DIFICIL:
                modoSeleccionado = DIFICIL;
                break;
        }

        JuegoSerpiente juego(modoSeleccionado);
        juego.Ejecutar();

        cout << "¡Juego terminado! Presiona cualquier tecla para volver al menu..." << endl;
        _getch();
    }

    return 0;
}
