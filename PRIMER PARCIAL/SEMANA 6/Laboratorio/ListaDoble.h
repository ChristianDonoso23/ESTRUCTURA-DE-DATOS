#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include "Nodo.cpp"

using namespace std;

class ListaDoble {
private:
    NodoDoble* cabeza;
    NodoDoble* cola;

public:
    ListaDoble();
    ~ListaDoble();
    void insertar(string& correo);
    bool buscar(string& correo);
    void imprimir();
};

#endif
