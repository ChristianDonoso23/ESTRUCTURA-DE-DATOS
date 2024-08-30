#include "Disco.h"
#include <graphics.h>

Disco::Disco(int num, int totalDiscos, int alturaTorre) {
    num_disco = num;
    altura_disco = 20;
    int ancho_base = 150;
    ancho_disco = ancho_base - (num * 10);
    pos_y = alturaTorre;
    color_disco = COLOR(255 - num * 20, 0 + num * 30, 0 + num * 50);
}

void Disco::setPosY(int nueva_pos_y) {
    pos_y = nueva_pos_y;
}

void Disco::dibujar(int posicion_x) const {
    setfillstyle(SOLID_FILL, color_disco);
    bar(posicion_x - ancho_disco / 2, pos_y - altura_disco, posicion_x + ancho_disco / 2, pos_y);
}
