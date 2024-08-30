#include <iostream>
#include <string>
#include <unistd.h>
#include <termios.h>
#include <fstream>
#include <limits>

#include "ListaDoble.cpp"

using namespace std;

int main() {
    ListaDoble *lista = new ListaDoble();
    int opcion; 
    char *dato;
    string primerNombre, segundoNombre, apellido;
    bool validacion1, validacion2;
    string txt = "datos.txt";

    while(opcion != 3) {
        cout << "1. Ingresar Datos" << endl;
        cout << "2. Mostrar Datos" << endl;
        cout << "3. Salir" << endl;
        dato = lista->ingresarNumeros("Ingrese una opcion: ", 1);
        opcion = atoi(dato);
        free(dato);

        switch(opcion) {
            case 1:
                primerNombre = lista->validarLetras("Ingrese primer nombre: ");
                segundoNombre = lista->validarLetras("Ingrese segundo nombre: ");
                apellido = lista->validarLetras("Ingrese apellido: ");

                do {
                    cout << "Ingrese cedula: ";
                    dato = lista->ingresarNumeros("", 10);
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
