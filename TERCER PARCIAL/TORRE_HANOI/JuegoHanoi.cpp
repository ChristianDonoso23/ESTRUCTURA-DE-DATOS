#include "JuegoHanoi.h"
#include <graphics.h>
#include <iostream>
#include <fstream>

JuegoHanoi::JuegoHanoi(int num, int numTorres, int torreOrigen) 
    : numDiscos(num), numTorres(numTorres) {
    // Asignar memoria para un array de punteros a torres usando malloc
    torres = (Torre**)malloc(numTorres * sizeof(Torre*));  // Usamos malloc para evitar corchetes

    if (torres == nullptr) {
        std::cerr << "Error al asignar memoria para las torres." << std::endl;
        exit(1);  // Salir si la asignación falla
    }

    int ancho_ventana = getmaxx();
    int espacio_entre_torres = ancho_ventana / (numTorres + 1);

    // Crear cada torre y asignarla a su respectivo puntero
    Torre** tempTorres = torres;
    for (int i = 0; i < numTorres; ++i) {
        *tempTorres = new Torre(300, numDiscos, espacio_entre_torres * (i + 1));
        tempTorres++;
    }

    // Añadir los discos a la torre de origen
    for (int i = 1; i <= numDiscos; ++i) {
        Disco* disco = new Disco(i, numDiscos, 300);
        (*(torres + torreOrigen))->agregarDisco(disco);
    }

    // Abrir el archivo para escribir los movimientos
    archivoMovimientos.open("movimientos.txt");
    if (!archivoMovimientos) {
        std::cerr << "Error al abrir el archivo de movimientos." << std::endl;
        exit(1);
    }

    dibujar();
}

void JuegoHanoi::moverDiscos(int numDiscos, int torreOrigen, int torreDestino, int torreAuxiliar) {
    if (numDiscos == 1) {
        Disco* disco = (*(torres + torreOrigen))->removerDisco();
        if (disco != nullptr) {
            (*(torres + torreDestino))->agregarDisco(disco);
            dibujar();
            delay(500);
            archivoMovimientos << "Disco movido de la torre " << (torreOrigen + 1) 
                               << " a la torre " << (torreDestino + 1) << "." << std::endl;
        }
    } else {
        moverDiscos(numDiscos - 1, torreOrigen, torreAuxiliar, torreDestino);
        Disco* disco = (*(torres + torreOrigen))->removerDisco();
        if (disco != nullptr) {
            (*(torres + torreDestino))->agregarDisco(disco);
            dibujar();
            delay(500);
            archivoMovimientos << "Disco movido de la torre " << (torreOrigen + 1) 
                               << " a la torre " << (torreDestino + 1) << "." << std::endl;
        }
        moverDiscos(numDiscos - 1, torreAuxiliar, torreDestino, torreOrigen);
    }
}

void JuegoHanoi::dibujar() {
    cleardevice();
    Torre** tempTorres = torres;
    for (int i = 0; i < numTorres; ++i) {
        (*tempTorres)->dibujar();
        tempTorres++;
    }
}

JuegoHanoi::~JuegoHanoi() {
    Torre** tempTorres = torres;
    for (int i = 0; i < numTorres; ++i) {
        delete *tempTorres;  // Liberar cada torre individualmente
        tempTorres++;
    }
    free(torres);  // Liberar la memoria asignada para el array de punteros
    
    // Cerrar el archivo de movimientos
    if (archivoMovimientos.is_open()) {
        archivoMovimientos.close();
    }
}
