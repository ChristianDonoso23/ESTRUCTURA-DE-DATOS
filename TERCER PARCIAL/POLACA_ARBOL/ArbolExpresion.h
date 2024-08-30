#ifndef ARBOLEXPRESION_H
#define ARBOLEXPRESION_H

#include <string>
#include "Nodo.cpp"

class ArbolExpresion {
public:
    Nodo* raiz;

    ArbolExpresion();
    Nodo* crearNodo(std::string valor);
    bool esNumero(std::string str);
    bool esOperador(char c);
    bool esFuncion(std::string token);
    bool validarInfija(std::string expresion);
    Nodo* construirArbol(std::string expresion);
    int precedencia(std::string operador);
    std::string obtenerInfija(Nodo* nodo);
    std::string obtenerSufija(Nodo* nodo);
    std::string obtenerPrefija(Nodo* nodo);
    double evaluarSufija(std::string sufija);
    void mostrarArbol(Nodo* nodo, int x, int y, int nivel);
    void dibujarLinea(int x1, int y1, int x2, int y2, int radio);
};

#endif
