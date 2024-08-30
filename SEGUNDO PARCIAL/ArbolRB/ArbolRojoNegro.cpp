#include "ArbolRojoNegro.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <graphics.h>
#include <cmath>
#include <queue>

ArbolRojoNegro::ArbolRojoNegro() {
    TNULL = new Nodo("", "", "", NEGRO);
    TNULL->setIzquierdo(nullptr);
    TNULL->setDerecho(nullptr);
    raiz = TNULL;
}

ArbolRojoNegro::~ArbolRojoNegro() {
    std::queue<Nodo*> nodes;
    nodes.push(raiz);
    while (!nodes.empty()) {
        Nodo* current = nodes.front();
        nodes.pop();
        if (current != TNULL) {
            nodes.push(current->getIzquierdo());
            nodes.push(current->getDerecho());
            delete current;
        }
    }
    delete TNULL;
}

Nodo* ArbolRojoNegro::getRaiz() const {
    return raiz;
}

Nodo* ArbolRojoNegro::getTNULL() const {
    return TNULL;
}

void ArbolRojoNegro::inicializarNodoNulo(Nodo*& nodo, Nodo*& padre) {
    nodo = TNULL;
    nodo->setPadre(padre);
}

bool ArbolRojoNegro::buscar(const std::string& cedula) const {
    if (raiz == TNULL) {
        std::cout << "El árbol está vacío." << std::endl;
        return false;
    }

    Nodo* nodo = buscarNodo(raiz, cedula);
    return nodo != TNULL;
}

Nodo* ArbolRojoNegro::buscarNodo(Nodo* nodo, const std::string& cedula) const {
    if (nodo == TNULL || cedula == nodo->getCedula()) {
        return nodo;
    }

    if (cedula < nodo->getCedula()) {
        return buscarNodo(nodo->getIzquierdo(), cedula);
    }
    return buscarNodo(nodo->getDerecho(), cedula);
}

Nodo* ArbolRojoNegro::minimo(Nodo* nodo) const {
    while (nodo->getIzquierdo() != TNULL) {
        nodo = nodo->getIzquierdo();
    }
    return nodo;
}

Nodo* ArbolRojoNegro::maximo(Nodo* nodo) const {
    while (nodo->getDerecho() != TNULL) {
        nodo = nodo->getDerecho();
    }
    return nodo;
}

void ArbolRojoNegro::insertar(const std::string& cedula, const std::string& nombre, const std::string& apellido) {
    Nodo* nodo = new Nodo(cedula, nombre, apellido);
    nodo->setPadre(nullptr);
    nodo->setIzquierdo(TNULL);
    nodo->setDerecho(TNULL);
    nodo->setColor(ROJO);

    Nodo* y = nullptr;
    Nodo* x = this->raiz;

    while (x != TNULL) {
        y = x;
        if (nodo->getCedula() < x->getCedula()) {
            x = x->getIzquierdo();
        } else {
            x = x->getDerecho();
        }
    }

    nodo->setPadre(y);
    if (y == nullptr) {
        raiz = nodo;
    } else if (nodo->getCedula() < y->getCedula()) {
        y->setIzquierdo(nodo);
    } else {
        y->setDerecho(nodo);
    }

    if (nodo->getPadre() == nullptr) {
        nodo->setColor(NEGRO);
        return;
    }

    if (nodo->getPadre()->getPadre() == nullptr) {
        return;
    }

    arreglarInsertar(nodo);
}

void ArbolRojoNegro::arreglarInsertar(Nodo*& k) {
    Nodo* u;
    while (k->getPadre()->getColor() == ROJO) {
        if (k->getPadre() == k->getPadre()->getPadre()->getDerecho()) {
            u = k->getPadre()->getPadre()->getIzquierdo();
            if (u->getColor() == ROJO) {
                u->setColor(NEGRO);
                k->getPadre()->setColor(NEGRO);
                k->getPadre()->getPadre()->setColor(ROJO);
                k = k->getPadre()->getPadre();
            } else {
                if (k == k->getPadre()->getIzquierdo()) {
                    k = k->getPadre();
                    rotarDerecha(k);
                }
                k->getPadre()->setColor(NEGRO);
                Nodo* abuelo = k->getPadre()->getPadre();
                abuelo->setColor(ROJO);
                rotarIzquierda(abuelo);
            }
        } else {
            u = k->getPadre()->getPadre()->getDerecho();

            if (u->getColor() == ROJO) {
                u->setColor(NEGRO);
                k->getPadre()->setColor(NEGRO);
                k->getPadre()->getPadre()->setColor(ROJO);
                k = k->getPadre()->getPadre();
            } else {
                if (k == k->getPadre()->getDerecho()) {
                    k = k->getPadre();
                    rotarIzquierda(k);
                }
                k->getPadre()->setColor(NEGRO);
                Nodo* abuelo = k->getPadre()->getPadre();
                abuelo->setColor(ROJO);
                rotarDerecha(abuelo);
            }
        }
        if (k == raiz) {
            break;
        }
    }
    raiz->setColor(NEGRO);
}

void ArbolRojoNegro::eliminar(const std::string& cedula) {
    if (raiz == TNULL) {
        std::cout << "El árbol está vacío." << std::endl;
        return;
    }

    Nodo* z = TNULL;
    Nodo* x, *y;
    Nodo* tempRaiz = raiz;
    while (tempRaiz != TNULL) {
        if (tempRaiz->getCedula() == cedula) {
            z = tempRaiz;
        }

        if (tempRaiz->getCedula() <= cedula) {
            tempRaiz = tempRaiz->getDerecho();
        } else {
            tempRaiz = tempRaiz->getIzquierdo();
        }
    }

    if (z == TNULL) {
        std::cout << "Dato no encontrado en el árbol." << std::endl;
        return;
    }

    y = z;
    Color y_original_color = y->getColor();
    if (z->getIzquierdo() == TNULL) {
        x = z->getDerecho();
        Nodo* zDerecho = z->getDerecho();
        transplantar(z, zDerecho);
    } else if (z->getDerecho() == TNULL) {
        x = z->getIzquierdo();
        Nodo* zIzquierdo = z->getIzquierdo();
        transplantar(z, zIzquierdo);
    } else {
        y = minimo(z->getDerecho());
        y_original_color = y->getColor();
        x = y->getDerecho();
        if (y->getPadre() == z) {
            x->setPadre(y);
        } else {
            Nodo* yDerecho = y->getDerecho();
            transplantar(y, yDerecho);
            y->setDerecho(z->getDerecho());
            y->getDerecho()->setPadre(y);
        }

        transplantar(z, y);
        y->setIzquierdo(z->getIzquierdo());
        y->getIzquierdo()->setPadre(y);
        y->setColor(z->getColor());
    }
    delete z;
    if (y_original_color == NEGRO) {
        arreglarEliminar(x);
    }
}

void ArbolRojoNegro::arreglarEliminar(Nodo*& x) {
    Nodo* s;
    while (x != raiz && x->getColor() == NEGRO) {
        if (x == x->getPadre()->getIzquierdo()) {
            s = x->getPadre()->getDerecho();
            if (s->getColor() == ROJO) {
                s->setColor(NEGRO);
                x->getPadre()->setColor(ROJO);
                Nodo* xPadre = x->getPadre();
                rotarIzquierda(xPadre);
                s = x->getPadre()->getDerecho();
            }

            if (s->getIzquierdo()->getColor() == NEGRO && s->getDerecho()->getColor() == NEGRO) {
                s->setColor(ROJO);
                x = x->getPadre();
            } else {
                if (s->getDerecho()->getColor() == NEGRO) {
                    s->getIzquierdo()->setColor(NEGRO);
                    s->setColor(ROJO);
                    rotarDerecha(s);
                    s = x->getPadre()->getDerecho();
                }

                s->setColor(x->getPadre()->getColor());
                x->getPadre()->setColor(NEGRO);
                s->getDerecho()->setColor(NEGRO);
                Nodo* xPadre = x->getPadre();
                rotarIzquierda(xPadre);
                x = raiz;
            }
        } else {
            s = x->getPadre()->getIzquierdo();
            if (s->getColor() == ROJO) {
                s->setColor(NEGRO);
                x->getPadre()->setColor(ROJO);
                Nodo* xPadre = x->getPadre();
                rotarDerecha(xPadre);
                s = x->getPadre()->getIzquierdo();
            }

            if (s->getDerecho()->getColor() == NEGRO && s->getDerecho()->getColor() == NEGRO) {
                s->setColor(ROJO);
                x = x->getPadre();
            } else {
                if (s->getIzquierdo()->getColor() == NEGRO) {
                    s->getDerecho()->setColor(NEGRO);
                    s->setColor(ROJO);
                    rotarIzquierda(s);
                    s = x->getPadre()->getIzquierdo();
                }

                s->setColor(x->getPadre()->getColor());
                x->getPadre()->setColor(NEGRO);
                s->getIzquierdo()->setColor(NEGRO);
                Nodo* xPadre = x->getPadre();
                rotarDerecha(xPadre);
                x = raiz;
            }
        }
    }
    x->setColor(NEGRO);
}

void ArbolRojoNegro::rotarIzquierda(Nodo*& x) {
    Nodo* y = x->getDerecho();
    x->setDerecho(y->getIzquierdo());
    if (y->getIzquierdo() != TNULL) {
        y->getIzquierdo()->setPadre(x);
    }
    y->setPadre(x->getPadre());
    if (x->getPadre() == nullptr) {
        raiz = y;
    } else if (x == x->getPadre()->getIzquierdo()) {
        x->getPadre()->setIzquierdo(y);
    } else {
        x->getPadre()->setDerecho(y);
    }
    y->setIzquierdo(x);
    x->setPadre(y);
}

void ArbolRojoNegro::rotarDerecha(Nodo*& x) {
    Nodo* y = x->getIzquierdo();
    x->setIzquierdo(y->getDerecho());
    if (y->getDerecho() != TNULL) {
        y->getDerecho()->setPadre(x);
    }
    y->setPadre(x->getPadre());
    if (x->getPadre() == nullptr) {
        raiz = y;
    } else if (x == x->getPadre()->getDerecho()) {
        x->getPadre()->setDerecho(y);
    } else {
        x->getPadre()->setIzquierdo(y);
    }
    y->setDerecho(x);
    x->setPadre(y);
}

void ArbolRojoNegro::transplantar(Nodo*& u, Nodo*& v) {
    if (u->getPadre() == nullptr) {
        raiz = v;
    } else if (u == u->getPadre()->getIzquierdo()) {
        u->getPadre()->setIzquierdo(v);
    } else {
        u->getPadre()->setDerecho(v);
    }
    v->setPadre(u->getPadre());
}

void ArbolRojoNegro::mostrarDatos() const {
    if (raiz == TNULL) {
        std::cout << "El árbol está vacío." << std::endl;
        return;
    }

    std::cout << "Cedula\tNombre\tApellido" << std::endl;
    std::cout << "-------------------------" << std::endl;
    preOrdenHelper(this->raiz);
    std::cout << std::endl;
}

void ArbolRojoNegro::preOrdenHelper(Nodo* nodo) const {
    if (nodo != TNULL) {
        std::cout << nodo->getCedula() << "\t" << nodo->getNombre() << "\t" << nodo->getApellido() << std::endl;
        preOrdenHelper(nodo->getIzquierdo());
        preOrdenHelper(nodo->getDerecho());
    }
}

void ArbolRojoNegro::graficarArbol() const {
    if (raiz == TNULL) {
        std::cout << "El árbol está vacío." << std::endl;
        return;
    }

    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    setbkcolor(WHITE);
    cleardevice();
    dibujarNodo(raiz, getmaxx() / 2, 50, getmaxx() / 4);
    getch();
    closegraph();
}

void ArbolRojoNegro::dibujarNodo(Nodo* nodo, int x, int y, int offset) const {
    if (nodo == TNULL || nodo->getCedula() == "") return;

    int color = (nodo->getColor() == ROJO) ? RED : BLACK;
    setfillstyle(SOLID_FILL, color);
    setcolor(color);
    fillellipse(x, y, 20, 20);

    setcolor(BLACK);
    outtextxy(x - 10, y - 10, const_cast<char*>(nodo->getCedula().c_str()));

    if (nodo->getIzquierdo() != TNULL) {
        line(x, y, x - offset, y + 60);
        dibujarNodo(nodo->getIzquierdo(), x - offset, y + 60, offset / 2);
    }
    if (nodo->getDerecho() != TNULL) {
        line(x, y, x + offset, y + 60);
        dibujarNodo(nodo->getDerecho(), x + offset, y + 60, offset / 2);
    }
}

void ArbolRojoNegro::guardarEnArchivo() const {
    std::string rutaArchivo = "usuarios.txt";
    std::ofstream archivo(rutaArchivo);
    
    // Verificación de apertura de archivo
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo para escribir: " << rutaArchivo << std::endl;
        return;
    }

    auto guardarNodoEnArchivo = [&archivo, this](Nodo* nodo, auto& ref) -> void {
        if (nodo == TNULL) return;
        archivo << nodo->getCedula() << "|" << nodo->getNombre() << "|" << nodo->getApellido() << std::endl;
        ref(nodo->getIzquierdo(), ref);
        ref(nodo->getDerecho(), ref);
    };

    // Guardando datos del árbol en preorden
    guardarNodoEnArchivo(raiz, guardarNodoEnArchivo);

    archivo.close();
    std::cout << "Datos guardados correctamente en " << rutaArchivo << std::endl;
}

void ArbolRojoNegro::cargarDesdeArchivo() {
    std::string rutaArchivo = "usuarios.txt";
    std::ifstream archivo(rutaArchivo);
    
    // Verificación de apertura de archivo
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo para leer: " << rutaArchivo << std::endl;
        return;
    }

    std::string linea;
    while (getline(archivo, linea)) {
        std::istringstream iss(linea);
        std::string numCedula, primerNombre, apellido;

        if (!getline(iss, numCedula, '|')) continue;
        if (!getline(iss, primerNombre, '|')) continue;
        if (!getline(iss, apellido, '|')) continue;

        insertar(numCedula, primerNombre, apellido);
    }

    archivo.close();
    std::cout << "Datos cargados correctamente desde " << rutaArchivo << std::endl;
}

