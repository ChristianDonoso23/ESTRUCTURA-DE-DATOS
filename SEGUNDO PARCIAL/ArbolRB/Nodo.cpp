#include "Nodo.h"

Nodo::Nodo(string cedula, string nombre, string apellido, Color color)
    : cedula(cedula), nombre(nombre), apellido(apellido), color(color), izquierdo(nullptr), derecho(nullptr), padre(nullptr) {}

// Getters
string Nodo::getCedula() const {
    return cedula;
}

string Nodo::getNombre() const {
    return nombre;
}

string Nodo::getApellido() const {
    return apellido;
}

Color Nodo::getColor() const {
    return color;
}

Nodo* Nodo::getIzquierdo() const {
    return izquierdo;
}

Nodo* Nodo::getDerecho() const {
    return derecho;
}

Nodo* Nodo::getPadre() const {
    return padre;
}

// Setters
void Nodo::setCedula(const string& cedula) {
    this->cedula = cedula;
}

void Nodo::setNombre(const string& nombre) {
    this->nombre = nombre;
}

void Nodo::setApellido(const string& apellido) {
    this->apellido = apellido;
}

void Nodo::setColor(Color color) {
    this->color = color;
}

void Nodo::setIzquierdo(Nodo* izquierdo) {
    this->izquierdo = izquierdo;
}

void Nodo::setDerecho(Nodo* derecho) {
    this->derecho = derecho;
}

void Nodo::setPadre(Nodo* padre) {
    this->padre = padre;
}
