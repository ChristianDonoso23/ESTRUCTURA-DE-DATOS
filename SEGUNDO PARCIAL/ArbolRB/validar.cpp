#include "validar.h"
#include "Nodo.h" // Asegúrate de que la definición de Nodo esté disponible
#include <iostream>
#include <conio.h>
#include <cctype>

bool validarCedula(long int cedula) {
    int i, A[10], res, mul, sumapares, sumaimpares, digito, sumatotal;
    long int cos;
    sumapares = 0;
    sumaimpares = 0;
    for (i = 9; i >= 0; i--) {
        cos = cedula / 10;
        res = cedula % 10;
        A[i] = res;
        cedula = cos;
    }
    for (i = 0; i < 9; i += 2) {
        mul = A[i] * 2;
        if (mul > 9)
            mul -= 9;
        sumapares += mul;
    }
    for (i = 1; i < 8; i += 2)
        sumaimpares += A[i];

    sumatotal = sumapares + sumaimpares;
    res = sumatotal % 10;
    digito = 10 - res;

    if (digito == 10)
        digito = 0;
    return digito == A[9];
}

bool esNumeroCedulaValido(const std::string &numCedula) {
    if (numCedula.length() != 10) return false;
    for (char c : numCedula) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

std::string ingresarCedula(const std::string &msj) {
    std::string dato = "";
    std::cout << msj << ": ";
    char c;
    while (true) {
        c = _getch(); // _getch() para obtener el carácter sin eco en pantalla
        if (isdigit(c)) {
            if (dato.length() < 10) {
                dato += c;
                std::cout << c;
            }
        } else if (c == 8) { // 8 es el código ASCII para la tecla de retroceso
            if (!dato.empty()) {
                dato.pop_back();
                std::cout << "\b \b"; // Eliminar el último carácter de la pantalla
            }
        } else if (c == 13) { // 13 es el código ASCII para la tecla Enter
            if (dato.length() == 10) {
                std::cout << std::endl;
                break;
            } else {
                std::cout << "\n>> Debe ingresar exactamente 10 números. Intente nuevamente." << std::endl;
                dato = "";
                std::cout << msj << ": ";
            }
        }
    }
    return dato;
}

bool cedulaRepetida(Nodo* raiz, const std::string &numCedula) {
    Nodo* nodo = raiz;
    while (nodo != nullptr) {
        if (nodo->getCedula() == numCedula) {
            return true;
        } else if (numCedula < nodo->getCedula()) {
            nodo = nodo->getIzquierdo();
        } else {
            nodo = nodo->getDerecho();
        }
    }
    return false;
}

string ingresarLetras(const std::string &msj, bool opcional) {
    string dato = "";
    cout << msj << ": ";
    char c;
    while ((c = getch()) != 13 || (!opcional && dato.empty())) {
        if (isalpha(c)) {
            dato += c;
            cout << c;
        } else if (c == 8) {
            if (!dato.empty()) {
                dato.pop_back();
                cout << "\b \b";
            }
        } else if (c == 13 && !dato.empty()) {
            break;
        }
    }
    cout << endl;
    return dato;
}