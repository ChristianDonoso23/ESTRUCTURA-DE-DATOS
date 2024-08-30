#ifndef VALIDAR_H
#define VALIDAR_H

#include <string>

bool validarCedula(long int cedula);
bool esNumeroCedulaValido(const std::string &numCedula);
std::string ingresarCedula(const std::string &msj);
bool cedulaRepetida(Nodo* raiz, const std::string &numCedula);
string ingresarLetras(const std::string &, bool opcional = false);
    
#endif // VALIDAR_H
