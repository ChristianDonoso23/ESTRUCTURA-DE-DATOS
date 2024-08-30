#include "Interfaz.h"

int Interfaz::obtenerNumeroConMensaje(const string& mensaje, int min, int max) {
    string entrada;
    char tecla;
    cout << mensaje;
    while (true) {
        tecla = _getch(); // Esperar la tecla de movimiento
        if (tecla == 13 && !entrada.empty()) { // Enter
            int numero = stoi(entrada);
            if (numero >= min && numero <= max) {
                cout << endl;
                return numero;
            } else {
                cout << "\nEl numero debe estar entre " << min << " y " << max << ". Intente de nuevo: " << endl;
                entrada.clear();
                cout << mensaje;
            }
        }
        if (isdigit(tecla)) {
            entrada += tecla;
            cout << tecla;
        } else if (tecla == 8 && !entrada.empty()) { // Backspace
            entrada.pop_back();
            cout << "\b \b";
        }
    }
}

void Interfaz::mostrarMenu(int& opcion) {
    int seleccion = 1; // Opción seleccionada por defecto
    char tecla;

    while (true) {
        system("cls"); // Limpiar la consola
        cout << "=== MENU ===" << endl;
        cout << (seleccion == 1 ? "-> " : "   ") << "1. Generar un nuevo laberinto con tamaño personalizado" << endl;
        cout << (seleccion == 2 ? "-> " : "   ") << "2. Cargar el laberinto generado y jugar" << endl;
        cout << (seleccion == 3 ? "-> " : "   ") << "3. Salir" << endl;

        tecla = _getch();

        if (tecla == 72) { // Flecha arriba
            seleccion = (seleccion == 1) ? 3 : seleccion - 1;
        } else if (tecla == 80) { // Flecha abajo
            seleccion = (seleccion == 3) ? 1 : seleccion + 1;
        } else if (tecla == 13) { // Enter
            opcion = seleccion;
            break;
        }
    }
}
