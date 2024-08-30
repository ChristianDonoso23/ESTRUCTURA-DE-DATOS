#ifndef ELIMINARCARACTER_H
#define ELIMINARCARACTER_H

#include <string>
#include <algorithm> 
#include <iostream>  

template<typename Nodo>
class EliminarCaracter {
public:
    std::string eliminarCaracterCadenaLambda(const std::string& str, char c);
    void eliminarCaracterListaRecursiva(Nodo* cabeza, char caracter);
    void eliminarCaracterListaCircular(Nodo* cabeza, char caracter);
};

#include "EliminarCaracter.cpp"

#endif // ELIMINARCARACTER_H
