#ifndef LABERINTO_H
#define LABERINTO_H

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

class Laberinto {
private:
    int ancho, alto;
    int** laberinto;

    bool esValida(int x, int y) const;
    void generar(int x, int y);

public:
    int* direccionX;
    int* direccionY;

    Laberinto(int ancho, int alto);
    ~Laberinto();

    void guardarEnArchivo(const string& nombreArchivo) const;
    static Laberinto* leerDesdeArchivo(const string& nombreArchivo, int& ancho, int& alto);
    void dibujar(int jugadorX, int jugadorY, int salidaX, int salidaY) const;
    bool moverJugador(int& jugadorX, int& jugadorY, char direccion, int salidaX, int salidaY);
    void actualizarCelda(int x, int y, int valor);
    void colocarSalida();
};

#endif // LABERINTO_H
