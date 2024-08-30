#ifndef LISTA_OBSTACULOS_H
#define LISTA_OBSTACULOS_H

#include "NodoObstaculo.h"

class ListaObstaculos {
public:
    ListaObstaculos() : cabeza(nullptr) {}
    ~ListaObstaculos() {
        while (cabeza) {
            EliminarFrente();
        }
    }
    
    void AgregarObstaculo(int x, int y) {
        cabeza = new NodoObstaculo(x, y, cabeza);
    }

    void EliminarFrente() {
        if (cabeza) {
            NodoObstaculo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }

    NodoObstaculo* ObtenerCabeza() const {
        return cabeza;
    }

private:
    NodoObstaculo* cabeza;
};

#endif // LISTA_OBSTACULOS_H
