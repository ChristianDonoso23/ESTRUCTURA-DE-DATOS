#ifndef LISTACIRCULAR_H
#define LISTACIRCULAR_H

#include "NodoCircular.h"
#include "..\Ordenador.h"
#include <string>

template <typename T>
class ListaCircular {
private:
    NodoCircular<T>* primero;
    NodoCircular<T>* ultimo;

public:
    ListaCircular();
    ~ListaCircular();
    void insertar(T, T, T);
    void buscar(T);
    void eliminar(T);
    void mostrar();
    bool cedulaRepetida(T);
    void guardarEnArchivo();
    void cargarDesdeArchivo();
    bool validarCedula(long int);
    T ingresarCedula(const std::string &);
    T ingresarOpcion(const std::string &, int, int);
    bool esNumeroCedulaValido(const T &);
    bool listaVacia();
    T ingresarNumeros(const std::string &);
    T ingresarLetras(const std::string &);
    T convertirMayusculas(T);
    NodoCircular<T>* getPrimero();
    /* Métodos de ordenamiento por intercambio */
    template <typename Compare>
    void ordenar(Compare comp);

    void ordenarCaracteresEnAtributo(const std::string& atributo);
    void guardarCaracteresOrdenadosEnArchivo(const std::string& atributo);
    /* Métodos de ordenamiento por burbuja*/
    template <typename Compare>
    void ordenarConBurbuja(Compare comp);
    
    void ordenarCaracteresBurbuja(const std::string& atributo);
    void guardarCaracteresOrdenadosBurbuja(const std::string& atributo);
    /* Métodos de ordenamiento Quicksort */
    template <typename Compare>
    void ordenarConQuickSortCirc(Compare comp);
    
    void ordenarCaracteresQuickSortCirc(const std::string& atributo);
    void guardarCaracteresOrdenadosQuickSortCirc(const std::string& atributo);
    /* Métodos de ordenamiento Shell Sort */
    template <typename Compare>
    void ordenarConShellSort(Compare comp);

    void ordenarCaracteresShellSort(const std::string& atributo);
    void guardarCaracteresOrdenadosShellsort(const std::string& atributo);
    /* Métodos de ordenamiento por Distribución*/
    template <typename Compare>
    void ordenarConDistribucion(Compare comp);
    
    void ordenarCaracteresDistribucion(const std::string& atributo);
    void guardarCaracteresOrdenadosDistribucion(const std::string& atributo);
    
    /* Métodos de ordenamiento Radix */
    template <typename Compare>
    void ordenarConRadix(Compare comp);
    void ordenarCaracteresRadix(const std::string& atributo);
    void guardarCaracteresOrdenadosRadixSort(const std::string& atributo);

    void mostrarCaracteresOrdenados();
    void resetLista();
};

#include "ListaCircular.cpp"
#endif // LISTACIRCULAR_H
