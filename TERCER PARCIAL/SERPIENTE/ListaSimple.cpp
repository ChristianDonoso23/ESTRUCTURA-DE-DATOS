#include "ListaSimple.h"
#include <cstdlib>

ListaSimple::ListaSimple() : cabeza(nullptr) {}

ListaSimple::~ListaSimple() {
    while (cabeza) {
        EliminarCola();
    }
}

void ListaSimple::AgregarFrente(int x, int y) {
    cabeza = new NodoSerpiente(x, y, cabeza);
}

void ListaSimple::EliminarCola() {
    if (!cabeza) return;
    if (!cabeza->siguiente) {
        delete cabeza;
        cabeza = nullptr;
        return;
    }

    NodoSerpiente* actual = cabeza;
    while (actual->siguiente && actual->siguiente->siguiente) {
        actual = actual->siguiente;
    }

    delete actual->siguiente;
    actual->siguiente = nullptr;
}

NodoSerpiente* ListaSimple::ObtenerCabeza() const {
    return cabeza;
}
