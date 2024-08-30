#ifndef LISTA_SIMPLE_H
#define LISTA_SIMPLE_H

#include "NodoSerpiente.h"

class ListaSimple {
public:
    ListaSimple();
    ~ListaSimple();
    void AgregarFrente(int x, int y);
    void EliminarCola();
    NodoSerpiente* ObtenerCabeza() const;

private:
    NodoSerpiente* cabeza;
};

#endif // LISTA_SIMPLE_H
