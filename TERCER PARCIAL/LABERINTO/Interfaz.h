#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <iostream>
#include <conio.h>

using namespace std;

class Interfaz {
public:
    static int obtenerNumeroConMensaje(const string& mensaje, int min, int max);
    static void mostrarMenu(int& opcion);
};

#endif // INTERFAZ_H
