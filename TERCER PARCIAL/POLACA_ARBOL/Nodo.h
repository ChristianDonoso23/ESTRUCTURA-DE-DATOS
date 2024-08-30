#ifndef NODO_H
#define NODO_H

#include <string>

struct Nodo {
    std::string dato;
    Nodo* izquierda;
    Nodo* derecha;

    Nodo(std::string valor);
};

#endif
