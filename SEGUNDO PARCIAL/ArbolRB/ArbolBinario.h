#ifndef ARBOLBINARIO_H
#define ARBOLBINARIO_H

#include "NodoBinario.cpp"  // Cambia a Nodo.h ya que Nodo.cpp ya no es necesario
#include <fstream>
#include <sstream>

class ArbolBinario {
private:
    Nodo* raiz;

    void preOrdenHelper(Nodo* nodo) const;
    Nodo* buscarNodo(Nodo* nodo, const std::string& cedula) const;
    void rotarIzquierda(Nodo*& nodo);
    void rotarDerecha(Nodo*& nodo);
    Nodo* minimo(Nodo* nodo) const;
    Nodo* maximo(Nodo* nodo) const;
    void dibujarNodo(Nodo* nodo, int x, int y, int offset) const;

public:
    ArbolBinario();
    ~ArbolBinario();

    void insertar(const std::string& cedula, const std::string& nombre, const std::string& apellido);
    void eliminar(const std::string& cedula);
    bool buscar(const std::string& cedula) const;
    void mostrarDatos() const;
    void graficarArbol() const;

    // Métodos para guardar y cargar desde archivo
    void guardarEnArchivo() const;
    void cargarDesdeArchivo();

    // Getter para la raíz
    Nodo* getRaiz() const;
};

#endif // ARBOLBINARIO_H
