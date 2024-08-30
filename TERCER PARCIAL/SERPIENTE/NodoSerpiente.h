#ifndef NODO_SERPIENTE_H
#define NODO_SERPIENTE_H

struct Posicion {
    int x, y;
};

class NodoSerpiente {
public:
    Posicion posicion;
    NodoSerpiente* siguiente;

    NodoSerpiente(int x, int y, NodoSerpiente* s = nullptr) : posicion{ x, y }, siguiente(s) {}
};

#endif // NODO_SERPIENTE_H
