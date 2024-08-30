#include "ArbolBinario.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <graphics.h>
#include <cmath>
#include <queue>

ArbolBinario::ArbolBinario() : raiz(nullptr) {}

ArbolBinario::~ArbolBinario() {
    std::queue<Nodo*> nodes;
    if (raiz != nullptr) {
        nodes.push(raiz);
    }
    while (!nodes.empty()) {
        Nodo* current = nodes.front();
        nodes.pop();
        if (current != nullptr) {
            nodes.push(current->getIzquierdo());
            nodes.push(current->getDerecho());
            delete current;
        }
    }
}

Nodo* ArbolBinario::getRaiz() const {
    return raiz;
}

void ArbolBinario::insertar(const std::string& cedula, const std::string& nombre, const std::string& apellido) {
    Nodo* nodo = new Nodo(cedula, nombre, apellido);
    nodo->setIzquierdo(nullptr);
    nodo->setDerecho(nullptr);

    Nodo* y = nullptr;
    Nodo* x = raiz;

    while (x != nullptr) {
        y = x;
        if (nodo->getCedula() < x->getCedula()) {
            x = x->getIzquierdo();
        } else {
            x = x->getDerecho();
        }
    }

    if (y == nullptr) {
        raiz = nodo;
    } else if (nodo->getCedula() < y->getCedula()) {
        y->setIzquierdo(nodo);
    } else {
        y->setDerecho(nodo);
    }
}

void ArbolBinario::eliminar(const std::string& cedula) {
    Nodo* z = buscarNodo(raiz, cedula);
    if (z == nullptr) {
        std::cout << "Dato no encontrado en el árbol." << std::endl;
        return;
    }

    Nodo* y;
    Nodo* x;

    if (z->getIzquierdo() == nullptr || z->getDerecho() == nullptr) {
        y = z;
    } else {
        y = minimo(z->getDerecho());
    }

    if (y->getIzquierdo() != nullptr) {
        x = y->getIzquierdo();
    } else {
        x = y->getDerecho();
    }

    if (x != nullptr) {
        x->setPadre(y->getPadre());
    }

    if (y->getPadre() == nullptr) {
        raiz = x;
    } else if (y == y->getPadre()->getIzquierdo()) {
        y->getPadre()->setIzquierdo(x);
    } else {
        y->getPadre()->setDerecho(x);
    }

    if (y != z) {
        z->setCedula(y->getCedula());
        z->setNombre(y->getNombre());
        z->setApellido(y->getApellido());
    }

    delete y;
}

bool ArbolBinario::buscar(const std::string& cedula) const {
    return buscarNodo(raiz, cedula) != nullptr;
}

Nodo* ArbolBinario::buscarNodo(Nodo* nodo, const std::string& cedula) const {
    if (nodo == nullptr || nodo->getCedula() == cedula) {
        return nodo;
    }

    if (cedula < nodo->getCedula()) {
        return buscarNodo(nodo->getIzquierdo(), cedula);
    }
    return buscarNodo(nodo->getDerecho(), cedula);
}

Nodo* ArbolBinario::minimo(Nodo* nodo) const {
    while (nodo->getIzquierdo() != nullptr) {
        nodo = nodo->getIzquierdo();
    }
    return nodo;
}

Nodo* ArbolBinario::maximo(Nodo* nodo) const {
    while (nodo->getDerecho() != nullptr) {
        nodo = nodo->getDerecho();
    }
    return nodo;
}

void ArbolBinario::mostrarDatos() const {
    if (raiz == nullptr) {
        std::cout << "El árbol está vacío." << std::endl;
        return;
    }

    std::cout << "Cedula\tNombre\tApellido" << std::endl;
    std::cout << "-------------------------" << std::endl;
    preOrdenHelper(this->raiz);
    std::cout << std::endl;
}

void ArbolBinario::preOrdenHelper(Nodo* nodo) const {
    if (nodo != nullptr) {
        std::cout << nodo->getCedula() << "\t" << nodo->getNombre() << "\t" << nodo->getApellido() << std::endl;
        preOrdenHelper(nodo->getIzquierdo());
        preOrdenHelper(nodo->getDerecho());
    }
}

void ArbolBinario::graficarArbol() const {
    if (raiz == nullptr) {
        std::cout << "El árbol está vacío." << std::endl;
        return;
    }

    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    setbkcolor(BLACK);
    cleardevice();
    dibujarNodo(raiz, getmaxx() / 2, 50, getmaxx() / 4);
    getch();
    closegraph();
}

void ArbolBinario::dibujarNodo(Nodo* nodo, int x, int y, int offset) const {
    if (nodo == nullptr || nodo->getCedula() == "") return;

    // Dibuja el nodo
    setfillstyle(SOLID_FILL, WHITE);
    setcolor(BLACK);
    fillellipse(x, y, 30, 30); // Aumentar el tamaño del nodo

    // Configura el color del texto
    setcolor(WHITE);

    // Obtiene el texto de la cédula y su tamaño
    std::string cedulaStr = nodo->getCedula();
    int textWidth = textwidth(const_cast<char*>(cedulaStr.c_str()));
    int textHeight = textheight(const_cast<char*>(cedulaStr.c_str()));

    // Ajusta la posición para centrar el texto en el nodo
    int textX = x - textWidth / 2;
    int textY = y - textHeight / 2;
    
    // Dibuja el texto en el centro del nodo
    outtextxy(textX, textY, const_cast<char*>(cedulaStr.c_str()));

    // Dibuja las líneas hacia los hijos
    if (nodo->getIzquierdo() != nullptr) {
        line(x, y, x - offset, y + 60);
        dibujarNodo(nodo->getIzquierdo(), x - offset, y + 60, offset / 2);
    }
    if (nodo->getDerecho() != nullptr) {
        line(x, y, x + offset, y + 60);
        dibujarNodo(nodo->getDerecho(), x + offset, y + 60, offset / 2);
    }
}


void ArbolBinario::guardarEnArchivo() const {
    std::string rutaArchivo = "usuarios.txt";
    std::ofstream archivo(rutaArchivo);
    
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo para escribir: " << rutaArchivo << std::endl;
        return;
    }

    auto guardarNodoEnArchivo = [&archivo, this](Nodo* nodo, auto& ref) -> void {
        if (nodo == nullptr) return;
        archivo << nodo->getCedula() << "|" << nodo->getNombre() << "|" << nodo->getApellido() << std::endl;
        ref(nodo->getIzquierdo(), ref);
        ref(nodo->getDerecho(), ref);
    };

    guardarNodoEnArchivo(raiz, guardarNodoEnArchivo);

    archivo.close();
    std::cout << "Datos guardados correctamente en " << rutaArchivo << std::endl;
}

void ArbolBinario::cargarDesdeArchivo() {
    std::string rutaArchivo = "usuarios.txt";
    std::ifstream archivo(rutaArchivo);
    
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
