#include "Laberinto.h"

Laberinto::Laberinto(int ancho, int alto) : ancho(ancho), alto(alto) {
    direccionX = new int[4]{0, 0, -1, 1};
    direccionY = new int[4]{-1, 1, 0, 0};

    laberinto = new int*[alto];
    for (int i = 0; i < alto; ++i) {
        laberinto[i] = new int[ancho];
        fill(laberinto[i], laberinto[i] + ancho, 1);
    }
    laberinto[1][1] = 0; // Punto de partida
    generar(1, 1);
}

Laberinto::~Laberinto() {
    for (int i = 0; i < alto; ++i) {
        delete[] laberinto[i];
    }
    delete[] laberinto;
    delete[] direccionX;
    delete[] direccionY;
}

void Laberinto::guardarEnArchivo(const string& nombreArchivo) const {
    ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        archivo << alto << " " << ancho << endl;  // Guardar las dimensiones del laberinto
        for (int i = 0; i < alto; ++i) {
            for (int j = 0; j < ancho; ++j) {
                archivo << laberinto[i][j] << " ";
            }
            archivo << endl;
        }
        archivo.close();
    }
}

Laberinto* Laberinto::leerDesdeArchivo(const string& nombreArchivo, int& ancho, int& alto) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return nullptr;
    }

    archivo >> alto >> ancho;

    Laberinto* laberinto = new Laberinto(ancho, alto);

    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
            archivo >> laberinto->laberinto[i][j];
        }
    }
    archivo.close();
    return laberinto;
}

void Laberinto::dibujar(int jugadorX, int jugadorY, int salidaX, int salidaY) const {
    system("cls"); // Limpiar la consola
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            if (i == jugadorY && j == jugadorX)
                cout << "P"; // P representa al jugador
            else if (i >= salidaY && i < salidaY + 2 && j >= salidaX && j < salidaX + 4)
                cout << "S"; // S representa la salida
            else if (laberinto[i][j] == 1)
                cout << "#"; // # representa un muro
            else
                cout << " "; // Espacio en blanco para el camino
        }
        cout << endl;
    }
}

bool Laberinto::moverJugador(int& jugadorX, int& jugadorY, char direccion, int salidaX, int salidaY) {
    int nuevoX = jugadorX;
    int nuevoY = jugadorY;

    switch (direccion) {
        case 'w': nuevoY--; break; // Arriba
        case 's': nuevoY++; break; // Abajo
        case 'a': nuevoX--; break; // Izquierda
        case 'd': nuevoX++; break; // Derecha
    }

    if (laberinto[nuevoY][nuevoX] == 0) {
        jugadorX = nuevoX;
        jugadorY = nuevoY;

        if (nuevoX >= salidaX && nuevoX < salidaX + 4 && nuevoY >= salidaY && nuevoY < salidaY + 2) {
            return true; // Indica que el jugador ha llegado a la salida
        }
    }

    return false;
}

void Laberinto::actualizarCelda(int x, int y, int valor) {
    if (x >= 0 && x < ancho && y >= 0 && y < alto) {
        laberinto[y][x] = valor;
    }
}

void Laberinto::colocarSalida() {
    int salidaX = ancho - 4;
    int salidaY = alto - 2;
    for (int i = salidaY; i < salidaY + 2; ++i) {
        for (int j = salidaX; j < salidaX + 4; ++j) {
            actualizarCelda(j, i, 0); // Colocar la salida
        }
    }
}

bool Laberinto::esValida(int x, int y) const {
    return x > 0 && x < ancho - 1 && y > 0 && y < alto - 1 && laberinto[y][x] == 1;
}

void Laberinto::generar(int x, int y) {
    int direcciones[4] = {0, 1, 2, 3}; // Representan arriba, abajo, izquierda, derecha
    random_shuffle(direcciones, direcciones + 4); // Mezclar las direcciones para aleatoriedad

    for (int i = 0; i < 4; ++i) {
        int dir = direcciones[i];
        int nx = x + direccionX[dir] * 2;
        int ny = y + direccionY[dir] * 2;

        if (esValida(nx, ny)) {
            laberinto[y + direccionY[dir]][x + direccionX[dir]] = 0;
            laberinto[ny][nx] = 0;
            generar(nx, ny);
        }
    }
}
