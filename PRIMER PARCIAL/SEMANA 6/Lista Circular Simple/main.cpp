#include <iostream>
#include <string>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>

#include "ListaCircularSimple.cpp"

using namespace std;

int main() {
    ListaCircularSimple *lista = new ListaCircularSimple();
    int opcion = 1;
    char cad[50];
    int longitud_cedula = 10;
    char *dato;
    string primerNombre, segundoNombre, apellido, inicio, correo;
    bool validacion1, validacion2;
    string txt = "datos.txt";

    while (opcion != 3) {
        cout << "1. Ingresar Datos" << endl;
        cout << "2. Mostrar Datos" << endl;
        cout << "3. Salir" << endl;
        cout << "Ingrese la opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese primer nombre: ";
                cin >> primerNombre;
                cout << "Ingrese segundo nombre: ";
                cin >> segundoNombre;
                cout << "Ingrese apellido: ";
                cin >> apellido;

                do {
                    dato = lista->ingresarNumeros("Ingrese cedula", longitud_cedula);
                    validacion1 = lista->validarCedula(dato);
                    validacion2 = lista->cedulaRepetida(dato);

                    if (!validacion1) {
                        cout << "Cédula incorrecta. Vuelva a ingresar." << endl;
                    } else if (validacion2) {
                        cout << "Cédula repetida. Vuelva a ingresar." << endl;
                    }
                } while (!validacion1 || validacion2);

                lista->guardarDatos(primerNombre, segundoNombre, apellido, dato);
                break;

            case 2:
                lista->mostrarDatos(txt);
                break;

            case 3:
                cout << "Saliendo..." << endl;
                break;

            default:
                cout << "Opción no válida." << endl;
        }
    }

    delete lista;
    return 0;
}
