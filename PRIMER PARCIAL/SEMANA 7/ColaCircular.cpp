/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Problema: Ejercicios colas y pilas 
 * Author:  Christian Estiven Donoso Cevallos
 * Fecha creacion: lunes, 17 de junio de 2024
 * Fecha modificacion: viernes , 21 de junio de 2024 
 ***********************************************************************/
#include <iostream>
#include <vector>

class ColaCircular {
private:
    std::vector<int> datos;
    int capacidad;
    int frente;
    int fin;
    int conteo;

public:
    ColaCircular(int cap) : capacidad(cap), frente(0), fin(-1), conteo(0) {
        datos.resize(capacidad);
    }

    void enqueue(int valor) {
        if (conteo == capacidad) {
            std::cout << "La cola está llena." << std::endl;
            return;
        }
        fin = (fin + 1) % capacidad;
        datos[fin] = valor;
        conteo++;
    }

    void dequeue() {
        if (conteo == 0) {
            std::cout << "La cola está vacía." << std::endl;
            return;
        }
        frente = (frente + 1) % capacidad;
        conteo--;
    }

    int front() {
        if (conteo == 0) {
            std::cout << "La cola está vacía." << std::endl;
            return -1;
        }
        return datos[frente];
    }

    bool empty() {
        return conteo == 0;
    }

    int size() {
        return conteo;
    }
};

int main() {
    ColaCircular cola(5);

    cola.enqueue(1);
    cola.enqueue(2);
    cola.enqueue(3);

    std::cout << "El primer elemento es: " << cola.front() << std::endl;
    cola.dequeue();
    std::cout << "El primer elemento después de eliminar uno es: " << cola.front() << std::endl;

    return 0;
}
