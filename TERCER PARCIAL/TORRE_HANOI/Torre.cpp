#include "Torre.h"
#include <graphics.h>
#include <iostream>

Torre::Torre(int altura, std::size_t capacidad_max, int posicion_x) 
    : altura_torre(altura), capacidad(capacidad_max), num_discos(0), posicion_x(posicion_x) {
    // Asignar memoria para un array de punteros a Disco usando malloc
    discos = (Disco**)malloc(capacidad * sizeof(Disco*));  // Usamos malloc para evitar corchetes

    if (discos == nullptr) {
        std::cerr << "Error al asignar memoria para los discos." << std::endl;
        exit(1);  // Salir si la asignación falla
    }

    // Inicializar los punteros de discos a nullptr
    Disco** temp = discos;
    for (std::size_t i = 0; i < capacidad; ++i) {
        *temp = nullptr;
        ++temp;
    }
}

void Torre::agregarDisco(Disco* disco) {
    if (num_discos < capacidad) {
        int nueva_pos_y = altura_torre - num_discos * disco->getAltura();
        disco->setPosY(nueva_pos_y);
        *(discos + num_discos) = disco;
        ++num_discos;
    } else {
        std::cout << "No se puede agregar más discos a esta torre." << std::endl;
    }
}

Disco* Torre::removerDisco() {
    if (num_discos > 0) {
        --num_discos;
        Disco* disco = *(discos + num_discos);
        *(discos + num_discos) = nullptr;
        return disco;
    } else {
        std::cout << "No hay discos en esta torre para remover." << std::endl;
        return nullptr;
    }
}

std::size_t Torre::getNumDiscos() const {
    return num_discos;
}

void Torre::dibujar() const {
    int ancho_torre = 20;
    int altura_torre_visual = 200;
    int radio = ancho_torre / 2;

    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);

    pieslice(posicion_x, altura_torre - altura_torre_visual + radio, 0, 180, radio);

    bar(posicion_x - radio, altura_torre - altura_torre_visual + radio,
        posicion_x + radio, altura_torre);

    Disco** temp = discos;
    for (std::size_t i = 0; i < num_discos; ++i) {
        if (*temp != nullptr) {
            (*temp)->dibujar(posicion_x);
        }
        ++temp;
    }
}

Torre::~Torre() {
    Disco** temp = discos;
    for (std::size_t i = 0; i < capacidad; ++i) {
        delete *temp;
        ++temp;
    }
    free(discos);
}
