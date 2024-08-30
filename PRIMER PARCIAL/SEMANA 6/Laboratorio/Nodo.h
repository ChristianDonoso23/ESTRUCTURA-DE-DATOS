#ifndef NODODOBLE_H
#define NODODOBLE_H

#include <string>

using namespace std;

class NodoDoble {
private:
    string correo;
    NodoDoble* siguiente;
    NodoDoble* anterior;

public:
    NodoDoble( string& correo);
    string getCorreo();
    NodoDoble* getSiguiente();
    NodoDoble* getAnterior();
    void setCorreo(string& correo);
    void setSiguiente(NodoDoble* siguiente);
    void setAnterior(NodoDoble* anterior);
};

#endif
