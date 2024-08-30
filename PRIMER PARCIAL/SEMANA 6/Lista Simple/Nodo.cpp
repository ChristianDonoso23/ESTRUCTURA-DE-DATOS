#include <iostream>
#include <string>
#include "Nodo.h"

using namespace std;

Nodo::Nodo() {
    this->dato = "";
    this->siguiente = NULL;
}

string Nodo::getDato() {
    return this->dato;
}

void Nodo::setDato(string dato) {
    this->dato = dato;
}

Nodo* Nodo::getSiguiente() {
    return this->siguiente;
}

void Nodo::setSiguiente(Nodo* siguiente) {
    this->siguiente = siguiente;
}
