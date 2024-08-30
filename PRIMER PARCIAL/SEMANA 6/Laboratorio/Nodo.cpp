#include "Nodo.h"

using namespace std;

NodoDoble::NodoDoble(string& correo) : correo(correo), siguiente(nullptr), anterior(nullptr) {}


string NodoDoble::getCorreo(){ 
    return correo; 
}

NodoDoble* NodoDoble::getSiguiente(){ 
    return siguiente; 
}

NodoDoble* NodoDoble::getAnterior(){ 
    return anterior; 
}

void NodoDoble::setCorreo(string& correo) { 
    this->correo = correo; 
}
void NodoDoble::setSiguiente(NodoDoble* siguiente) { 
    this->siguiente = siguiente;
}

void NodoDoble::setAnterior(NodoDoble* anterior) { 
    this->anterior = anterior; 
}
