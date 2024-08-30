/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Ejercicios lista
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 10 de junio de 2024
 * Fecha modificacion: viernes , 14 de junio de 2024 
 ***********************************************************************/
#include <iostream>

// Definición de la clase Nodo
class Nodo {
public:
    int dato;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(int valor) : dato(valor), siguiente(nullptr), anterior(nullptr) {}
};

// Función para insertar un nodo al principio
void insertarInicio(Nodo*& cabeza, int valor) {
    Nodo* nuevo = new Nodo(valor);
    if (cabeza == nullptr) {
        nuevo->siguiente = nuevo;
        nuevo->anterior = nuevo;
        cabeza = nuevo;
    } else {
        Nodo* ultimo = cabeza->anterior;
        nuevo->siguiente = cabeza;
        nuevo->anterior = ultimo;
        cabeza->anterior = nuevo;
        ultimo->siguiente = nuevo;
        cabeza = nuevo;
    }
}

// Función para imprimir la lista
void imprimirLista(Nodo* cabeza) {
    if (cabeza == nullptr) return;
    Nodo* actual = cabeza;
    do {
        std::cout << actual->dato << " <-> ";
        actual = actual->siguiente;
    } while (actual != cabeza);
    std::cout << "(cabeza)" << std::endl;
}

int main() {
    Nodo* cabeza = nullptr;
    insertarInicio(cabeza, 1);
    insertarInicio(cabeza, 2);
    insertarInicio(cabeza, 3);

    imprimirLista(cabeza);

    return 0;
}
