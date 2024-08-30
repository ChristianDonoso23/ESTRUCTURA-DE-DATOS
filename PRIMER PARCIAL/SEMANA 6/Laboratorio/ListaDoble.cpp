#include "ListaDoble.h"
#include <iostream>

using namespace std;

ListaDoble::ListaDoble() : cabeza(nullptr), cola(nullptr) {}

ListaDoble::~ListaDoble() {
    NodoDoble* actual = cabeza;
    while (actual != nullptr) {
        NodoDoble* siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
}

void ListaDoble::insertar(string& correo) {
    NodoDoble* nuevoNodo = new NodoDoble(correo);
    if (cabeza == nullptr) {
        cabeza = cola = nuevoNodo;
    } else {
        cola->setSiguiente(nuevoNodo);
        nuevoNodo->setAnterior(cola);
        cola = nuevoNodo;
    }
}

bool ListaDoble::buscar(string& correo){
    NodoDoble* actual = cabeza;
    while (actual != nullptr) {
        if (actual->getCorreo() == correo) {
            return true;
        }
        actual = actual->getSiguiente();
    }
    return false;
}

void ListaDoble::imprimir(){
    NodoDoble* actual = cabeza;
    while (actual != nullptr) {
        std::cout << actual->getCorreo() << std::endl;
        actual = actual->getSiguiente();
    }
}
