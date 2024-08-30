#include <iostream>
#include <conio.h>
#include <graphics.h>
#include "nreinas.cpp"
#include "tablero.cpp"
#include "caballo.cpp"
#include "alfil.cpp"
#include "torre.cpp"
#include "peon.cpp"
#include "rey.cpp"

using namespace std;

void mostrarMenu(int opcionSeleccionada) {
    system("cls");
    cout << "MENU PRINCIPAL\n";
    for (int i = 1; i <= 9; ++i) {
        if (i == opcionSeleccionada) {
            cout << "-> ";
        } else {
            cout << "   ";
        }
        switch (i) {
            case 1:
                cout << "Mostrar tablero de ajedrez sin piezas\n";
                break;
            case 2:
                cout << "Mostrar tablero de ajedrez con piezas\n";
                break;
            case 3:
                cout << "Resolver el problema de N-Reinas\n";
                break;
            case 4:
                cout << "Mostrar movimientos del caballo en el tablero\n";
                break;
            case 5:
                cout << "Mostrar movimientos del alfil en el tablero\n";
                break;
            case 6:
                cout << "Mostrar movimientos de la torre en el tablero\n";
                break;
            case 7:
                cout << "Mostar movimientos del peon en el tablero\n";
                break;
            case 8:
                cout << "Mostrar movimientos del rey en el tablero\n";
                break;
            case 9:
                cout << "Salir\n";
                break;
        }
    }
}

int obtenerNumero() {
    string entrada;
    char tecla;
    cout << "Ingrese el numero de reinas: ";
    while (true) {
        tecla = _getch();
        if (tecla == 13 && !entrada.empty()) {
            int numero = stoi(entrada);
            if (numero > 3) {
                cout << endl;
                return numero;
            } else {
                cout << "\nEl numero debe ser mayor que 3. Intente de nuevo: ";
                entrada.clear();
            }
        }
        if (isdigit(tecla)) {
            entrada += tecla;
            cout << tecla;
        } else if (tecla == 8 && !entrada.empty()) {
            entrada.pop_back();
            cout << "\b \b";
        }
    }
}

void ejecutarMenu() {
    int opcionSeleccionada = 1;
    int tecla;

    while (true) {
        mostrarMenu(opcionSeleccionada);

        tecla = _getch();

        if (tecla == 224) {
            tecla = _getch();
            switch (tecla) {
                case 72:
                    if (opcionSeleccionada > 1) {
                        opcionSeleccionada--;
                    }
                    break;
                case 80:
                    if (opcionSeleccionada < 9) {
                        opcionSeleccionada++;
                    }
                    break;
            }
        } else if (tecla == 13) {
            switch (opcionSeleccionada) {
                case 1:
                    mostrarTableroSinPiezas();
                    break;
                case 2:
                    mostrarTableroConPiezas();
                    break;
                case 3: {
                    int n = obtenerNumero();
                    ejecutarNReinas(n);
                    break;
                }
                case 4: {
                    ejecutarCaballo(8);
                    break;
                }
                case 5: {
                    ejecutarAlfil(8);
                    break;
                }
                case 6: {
                    ejecutarTorre(8);
                    break;
                }
                case 7: {
                    ejecutarPeon(8);
                    break;
                }
                case 8: {
                    ejecutarRey(8);
                    break;
                }
                case 9:
                    cout << "Saliendo del programa.\n";
                    return;
            }
        }
    }
}

int main() {
    ejecutarMenu();
    return 0;
}
