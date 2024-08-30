#ifndef DISCO_H
#define DISCO_H

class Disco {
public:
    Disco(int num, int totalDiscos, int alturaTorre);
    void setPosY(int nueva_pos_y);  // Declaración de setPosY
    void dibujar(int posicion_x) const;
    int getAltura() const { return altura_disco; }  // Función para obtener la altura del disco
private:
    int num_disco;
    int altura_disco;
    int ancho_disco;
    int pos_y;
    int color_disco;  // Añadir el atributo para almacenar el color del disco
};

#endif // DISCO_H
