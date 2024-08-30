#include <iostream>
#include <conio.h>
#include <limits>
#include <cctype>
#include "Conjunto.h"
#include "Grafico.h"
#include "Menu.h"

using namespace std;

int obtenerNumero() {
    string entrada;
    char tecla;
    cout << "Ingrese el numero de elementos del conjunto: ";
    while (true) {
        tecla = _getch();
        if (tecla == 13 && !entrada.empty()) {
            try {
                int numero = stoi(entrada);
                if (numero > 0) {
                    cout << endl;
                    return numero;
                } else {
                    cout << "\nEl numero debe ser mayor que 0. Intente de nuevo: ";
                    entrada.clear();
                }
            } catch (invalid_argument&) {
                cout << "\nEntrada no válida. Intente de nuevo: ";
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

int main() {
    Grafico grafico;
    grafico.inicializarGraficos();

    const string menuOpciones[] = {"Operaciones con conjuntos", "Salir"};
    const string menuOperaciones[] = {"Union", "Interseccion", "Diferencia", "Complemento", "Mostrar conjuntos", "Regresar"};
    const string menuDiferencias[] = {"A - B", "B - A", "Regresar"};
    const string menuComplemento[] = {"Complemento de A", "Complemento de B", "Regresar"};

    while (true) {
        int opcion = Menu::mostrarMenu(menuOpciones, 2);

        if (opcion == 1) {
            break;
        }

        int tamA, tamB, tamU;

        system("cls");
        tamA = obtenerNumero();
        auto A = Conjunto<string>::asignarMemoria(tamA);
        Conjunto<string>::ingresarConjunto(A, tamA, 'A',1);

        tamB = obtenerNumero();
        auto B = Conjunto<string>::asignarMemoria(tamB);
        Conjunto<string>::ingresarConjunto(B, tamB, 'B',1);

        auto universo = Conjunto<string>::unionConjuntos(A, tamA, B, tamB, tamU);

        while (true) {
            int opcionOperacion = Menu::mostrarMenu(menuOperaciones, 6);

            if (opcionOperacion == 5) {
                break;
            }

            system("cls");

            switch (opcionOperacion) {
                case 0: {
                    grafico.graficarUnion(A, tamA, B, tamB);
                    break;
                }
                case 1: {
                    grafico.graficarInterseccion(A, tamA, B, tamB);
                    break;
                }
                case 2: {
                    int opcionDiferencia = Menu::mostrarMenu(menuDiferencias, 3);
                    if (opcionDiferencia == 2) break;

                    if (opcionDiferencia == 0) {
                        grafico.graficarDiferencia(A, tamA, B, tamB, true);
                    } else if (opcionDiferencia == 1) {
                        grafico.graficarDiferencia(A, tamA, B, tamB, false);
                    }
                    break;
                }
                case 3: {
                    int opcionComplemento = Menu::mostrarMenu(menuComplemento, 3);
                    if (opcionComplemento == 2) break;

                    if (opcionComplemento == 0) {
                        grafico.graficarComplemento(universo, tamU, A, tamA, true);
                    } else if (opcionComplemento == 1) {
                        grafico.graficarComplemento(universo, tamU, B, tamB, false);
                    }
                    break;
                }
                case 4: {
                    grafico.graficarConjuntosSeparados(A, tamA, B, tamB);
                    break;
                }
            }

            cout << "\nPresione cualquier tecla para continuar...";
            _getch();
        }

        delete[] universo;
        delete[] A;
        delete[] B;
    }

    closegraph();
    return 0;
}
