#include <iostream>
#include <conio.h>
#include <windows.h>
#include "ArbolBinario.cpp" // Cambiado a ArbolBinario.cpp
#include "validar.cpp" // Incluir el archivo de cabecera para las validaciones

using namespace std;

void gotoxy(int x, int y);
void printMenu(const char* menu[], int size, int currentSelection);

int main() {
    system("cls");
    ArbolBinario arbol; // Cambiado a ArbolBinario

    // Cargar datos desde archivo al iniciar el programa
    arbol.cargarDesdeArchivo();

    const char* menu[] = {
        "Ingresar dato",
        "Buscar dato",
        "Eliminar dato",
        "Mostrar datos",
        "Graficar arbol",
        "Salir"
    };
    int size = sizeof(menu) / sizeof(menu[0]);
    int currentSelection = 0;
    int key;

    do {
        system("cls");
        cout << "\t\t.:MENU DE ARBOL BINARIO:." << endl; // Cambiado a Arbol Binario
        printMenu(menu, size, currentSelection);

        key = _getch();

        switch (key) {
            case 72: // Flecha arriba
                if (currentSelection > 0) {
                    currentSelection--;
                }
                break;
            case 80: // Flecha abajo
                if (currentSelection < size - 1) {
                    currentSelection++;
                }
                break;
            case 13: // Enter
                switch (currentSelection) {
                    case 0: {
                        string cedula = ingresarCedula("Ingrese la cedula");
                        long int cedulaNum;
                        try {
                            cedulaNum = stol(cedula);
                        } catch (exception& e) {
                            cout << "Error de conversión de cédula." << endl;
                            break;
                        }

                        if (validarCedula(cedulaNum)) {
                            if (!cedulaRepetida(arbol.getRaiz(), cedula)) {
                                string nombre, apellido;
                                cout << "Ingrese el nombre: ";
                                cin >> nombre;
                                cout << "Ingrese el apellido: ";
                                cin >> apellido;
                                arbol.insertar(cedula, nombre, apellido);
                                arbol.guardarEnArchivo(); // Guardar después de insertar
                                cout << "Datos ingresados y guardados correctamente." << endl;
                            } else {
                                cout << "Cédula ya existe en el sistema." << endl;
                            }
                        } else {
                            cout << "Cédula no válida." << endl;
                        }
                        break;
                    }
                    case 1: {
                        if (arbol.getRaiz() == nullptr) { // Cambiado a nullptr
                            cout << "El árbol está vacío." << endl;
                        } else {
                            string cedula;
                            cout << "Ingrese la cedula del dato a buscar: ";
                            cin >> cedula;
                            if (arbol.buscar(cedula)) {
                                cout << "Dato encontrado." << endl;
                            } else {
                                cout << "Dato no encontrado." << endl;
                            }
                        }
                        break;
                    }
                    case 2: {
                        if (arbol.getRaiz() == nullptr) { // Cambiado a nullptr
                            cout << "El árbol está vacío." << endl;
                        } else {
                            string cedula;
                            cout << "Ingrese la cedula del dato a eliminar: ";
                            cin >> cedula;
                            arbol.eliminar(cedula);
                            arbol.guardarEnArchivo(); // Guardar después de eliminar
                            cout << "Dato eliminado y cambios guardados correctamente." << endl;
                        }
                        break;
                    }
                    case 3: {
                        if (arbol.getRaiz() == nullptr) { // Cambiado a nullptr
                            cout << "El árbol está vacío." << endl;
                        } else {
                            arbol.mostrarDatos();
                        }
                        break;
                    }
                    case 4: {
                        if (arbol.getRaiz() == nullptr) { // Cambiado a nullptr
                            cout << "El árbol está vacío." << endl;
                        } else {
                            arbol.graficarArbol();
                        }
                        break;
                    }
                    case 5:
                        cout << "Saliendo del programa..." << endl;
                        return 0;
                    default:
                        cout << "Opción inválida. Inténtalo nuevamente." << endl;
                        break;
                }
                if (currentSelection != 5) {
                    cout << "Presione cualquier tecla para continuar..." << endl;
                    _getch();
                }
                break;
        }
    } while (true);

    return 0;
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printMenu(const char* menu[], int size, int currentSelection) {
    for (int i = 0; i < size; ++i) {
        if (i == currentSelection) {
            cout << "> " << menu[i] << " <" << endl;
        } else {
            cout << "  " << menu[i] << endl;
        }
    }
}
