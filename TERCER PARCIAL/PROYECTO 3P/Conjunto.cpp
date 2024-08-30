#include "Conjunto.h"
using namespace std;

template <typename T>
T* Conjunto<T>::asignarMemoria(int tamano) {
    return new T[tamano];
}

template <typename T>
bool Conjunto<T>::existeEnConjunto(const T* conjunto, int tamano, T elemento) {
    if (tamano == 0) {
        return false;
    }
    if (*conjunto == elemento) {
        return true;
    }
    return existeEnConjunto(conjunto + 1, tamano - 1, elemento);
}

template <typename T>
void Conjunto<T>::ingresarConjunto(T* conjunto, int tamano, char nombreConjunto, int indiceElemento) {
    if (tamano == 0) {
        return;
    }
    if (indiceElemento == 1) {
        cout << "ELEMENTOS DEL CONJUNTO " << nombreConjunto << endl;
    }

    std::string entrada;
    char tecla;
    T elemento;
    bool esValido = false;

    while (!esValido) {
        entrada.clear();
        cout << "Elemento " << indiceElemento << ": ";

        while (true) {
            tecla = _getch();

            if (tecla == 13 && !entrada.empty()) {
                std::istringstream iss(entrada);
                if (iss >> elemento) {
                    esValido = true;
                    cout << endl;
                    break;
                } else {
                    cout << "\nEntrada no válida. Intente de nuevo: ";
                    entrada.clear();
                    break;
                }
            }

            if (tecla == 8 && !entrada.empty()) {
                entrada.pop_back();
                cout << "\b \b";
            } else if (!isspace(tecla) && tecla != 13 && tecla != 8) {
                entrada += tecla;
                cout << tecla;
            }
        }
    }

    if (!existeEnConjunto(conjunto - (indiceElemento - 1), indiceElemento - 1, elemento)) {
        *conjunto = elemento;
        ingresarConjunto(conjunto + 1, tamano - 1, nombreConjunto, indiceElemento + 1);
    } else {
        ingresarConjunto(conjunto, tamano, nombreConjunto, indiceElemento);
    }
}

template <typename T>
T* Conjunto<T>::unionConjuntos(T* A, int tamA, T* B, int tamB, int& tamUnion) {
    tamUnion = tamA + tamB;
    T* unionAB = asignarMemoria(tamUnion);

    T* ptrA = A;
    T* ptrB = B;
    T* ptrUnion = unionAB;

    for (int i = 0; i < tamA; ++i) {
        *ptrUnion++ = *ptrA++;
    }

    ptrA = A;
    for (int i = 0; i < tamB; ++i) {
        bool encontrado = false;
        T* ptrCheck = ptrA;
        for (int j = 0; j < tamA; ++j) {
            if (*ptrB == *ptrCheck) {
                encontrado = true;
                break;
            }
            ++ptrCheck;
        }
        if (!encontrado) {
            *ptrUnion++ = *ptrB;
        }
        ++ptrB;
    }

    tamUnion = ptrUnion - unionAB;
    return unionAB;
}

template <typename T>
T* Conjunto<T>::interseccionConjuntos(T* A, int tamA, T* B, int tamB, int& tamInterseccion, int idxA, int idxI) {
    if (idxA == tamA) {
        tamInterseccion = idxI;
        return asignarMemoria(tamInterseccion);
    }

    auto verificarElemento = [B, tamB](T elemento) -> bool {
        auto buscarEnB = [&buscarEnB, B, tamB](int index, T elemento) -> bool {
            if (index == tamB) {
                return false;
            }
            if (*(B + index) == elemento) {
                return true;
            }
            return buscarEnB(index + 1, elemento);
        };
        return buscarEnB(0, elemento);
    };

    bool encontrado = verificarElemento(*(A + idxA));

    T* interseccionAB = interseccionConjuntos(A, tamA, B, tamB, tamInterseccion, idxA + 1, idxI + (encontrado ? 1 : 0));

    if (encontrado) {
        *(interseccionAB + idxI) = *(A + idxA);
    }

    return interseccionAB;
}

template <typename T>
T* Conjunto<T>::diferenciaAmenosB(T* A, int tamA, T* B, int tamB, int& tamDiferencia, int idxA, int idxD) {
    if (idxA == tamA) {
        tamDiferencia = idxD;
        return asignarMemoria(tamDiferencia);
    }

    auto verificarElemento = [B, tamB](T elemento) -> bool {
        T* ptrB = B;
        int idx = 0;
        while (idx < tamB) {
            if (*ptrB == elemento) {
                return true;
            }
            ++ptrB;
            ++idx;
        }
        return false;
    };

    bool encontrado = verificarElemento(*(A + idxA));

    T* diferenciaAB = diferenciaAmenosB(A, tamA, B, tamB, tamDiferencia, idxA + 1, idxD + (encontrado ? 0 : 1));

    if (!encontrado) {
        *(diferenciaAB + idxD) = *(A + idxA);
    }

    return diferenciaAB;
}

template <typename T>
T* Conjunto<T>::diferenciaBmenosA(T* B, int tamB, T* A, int tamA, int& tamDiferencia, int idxB, int idxD) {
    if (idxB == tamB) {
        tamDiferencia = idxD;
        return asignarMemoria(tamDiferencia);
    }

    auto verificarElemento = [A, tamA](T elemento) -> bool {
        T* ptrA = A;
        int idx = 0;
        while (idx < tamA) {
            if (*ptrA == elemento) {
                return true;
            }
            ++ptrA;
            ++idx;
        }
        return false;
    };

    bool encontrado = verificarElemento(*(B + idxB));

    T* diferenciaBA = diferenciaBmenosA(B, tamB, A, tamA, tamDiferencia, idxB + 1, idxD + (encontrado ? 0 : 1));

    if (!encontrado) {
        *(diferenciaBA + idxD) = *(B + idxB);
    }

    return diferenciaBA;
}

template <typename T>
T* Conjunto<T>::complementoConjunto(T* universo, int tamU, T* A, int tamA, int& tamComplemento, int idxU, int idxC) {
    if (idxU == tamU) {
        tamComplemento = idxC;
        return asignarMemoria(tamComplemento);
    }

    auto verificarElemento = [A, tamA](T elemento) -> bool {
        T* ptrA = A;
        int idx = 0;
        while (idx < tamA) {
            if (*ptrA == elemento) {
                return true;
            }
            ++ptrA;
            ++idx;
        }
        return false;
    };

    bool encontrado = verificarElemento(*(universo + idxU));

    T* complementoA = complementoConjunto(universo, tamU, A, tamA, tamComplemento, idxU + 1, idxC + (encontrado ? 0 : 1));

    if (!encontrado) {
        *(complementoA + idxC) = *(universo + idxU);
    }

    return complementoA;
}