#include "EliminarCaracter.h"
#include "../ProyectoGrupalPrueba(2)/ListaSimple/NodoSimple.h"
#include "../ProyectoGrupalPrueba(2)/ListaDoble/NodoDoble.h"
#include "../ProyectoGrupalPrueba(2)/ListaCircular/NodoCircular.h"
template<typename Nodo>
std::string EliminarCaracter<Nodo>::eliminarCaracterCadenaLambda(const std::string& str, char c) {
    std::string resultado;
    auto eliminar = [&resultado, c](char ch) {
        if (ch != c) {
            resultado += ch;
        }
    };
    for (char ch : str) {
        eliminar(ch);
    }

    return resultado;
}

template<typename Nodo>
void EliminarCaracter<Nodo>::eliminarCaracterListaRecursiva(Nodo* actual, char caracter) {
    if (actual != nullptr) {
        std::string apellido = actual->getApellido();
        apellido = eliminarCaracterCadenaLambda(apellido, caracter);
        actual->setApellido(apellido);
        std::cout << "Apellido modificado: " << actual->getApellido() << std::endl;
        eliminarCaracterListaRecursiva(actual->getSiguiente(), caracter);
    }
}

template<typename Nodo>
void EliminarCaracter<Nodo>::eliminarCaracterListaCircular(Nodo* cabeza, char caracter) {
    if (cabeza == nullptr) {
        return;  
    }

    Nodo* actual = cabeza;
    do {
        std::string apellido = actual->getApellido();
        apellido = eliminarCaracterCadenaLambda(apellido, caracter);
        actual->setApellido(apellido);
        std::cout << "Apellido modificado: " << actual->getApellido() << std::endl;

        actual = actual->getSiguiente();
    } while (actual != cabeza);
}

template class EliminarCaracter<NodoSimple<std::string>>;
template class EliminarCaracter<NodoDoble<std::string>>;
template class EliminarCaracter<NodoCircular<std::string>>;
