#ifndef NODO_H
#define NODO_H
#include <iostream>
#include <string>

using namespace std;

class Nodo {
private:
    string dato;
    Nodo* siguiente;
public:
    Nodo();
    string getDato();
    void setDato(string);
    Nodo* getSiguiente();
    void setSiguiente(Nodo*);
};
#endif  // NODO_H
