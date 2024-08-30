#ifndef NODO_OBSTACULO_H
#define NODO_OBSTACULO_H

struct PosicionObstaculo {
    int x, y;
};

class NodoObstaculo {
public:
    PosicionObstaculo posicion;
    NodoObstaculo* siguiente;

    NodoObstaculo(int x, int y, NodoObstaculo* s = nullptr) : posicion{ x, y }, siguiente(s) {}
};

#endif // NODO_OBSTACULO_H
