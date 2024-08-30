#ifndef ARBOLROJONEGRO_H
#define ARBOLROJONEGRO_H

#include "Nodo.cpp"
#include <fstream>
#include <sstream>

class ArbolRojoNegro {
private:
    Nodo* raiz;
    Nodo* TNULL;

    void inicializarNodoNulo(Nodo*& nodo, Nodo*& padre);
    void preOrdenHelper(Nodo* nodo) const;
    Nodo* buscarNodo(Nodo* nodo, const std::string& cedula) const;
    void arreglarInsertar(Nodo*& nodo);
    void arreglarEliminar(Nodo*& nodo);
    void rotarIzquierda(Nodo*& nodo);
    void rotarDerecha(Nodo*& nodo);
    void transplantar(Nodo*& u, Nodo*& v);
    Nodo* minimo(Nodo* nodo) const;
    Nodo* maximo(Nodo* nodo) const;
    void dibujarNodo(Nodo* nodo, int x, int y, int offset) const;

public:
    ArbolRojoNegro();
    ~ArbolRojoNegro();

    void insertar(const std::string& cedula, const std::string& nombre, const std::string& apellido);
    void eliminar(const std::string& cedula);
    bool buscar(const std::string& cedula) const;
    void mostrarDatos() const;
    void graficarArbol() const;

    // Métodos para guardar y cargar desde archivo
    void guardarEnArchivo() const;
    void cargarDesdeArchivo();

    // Getters para la raíz y el nodo nulo
    Nodo* getRaiz() const;
    Nodo* getTNULL() const;
};

#endif // ARBOLROJONEGRO_H
