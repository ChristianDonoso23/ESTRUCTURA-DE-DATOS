#include "CuadroLatino.h"
#include <conio.h>
#include <limits>

// Constructor para inicializar el cuadrado latino
CuadradoLatino::CuadradoLatino(int orden) : n(orden) {
    // Asignar memoria dinámica para el cuadrado latino
    cuadradoLatino = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        *(cuadradoLatino + i) = (int*)malloc(n * sizeof(int));
    }

    // Asignar memoria dinámica para los números
    numeros = (int*)malloc(n * sizeof(int));
}

// Destructor para liberar memoria
CuadradoLatino::~CuadradoLatino() {
    for (int i = 0; i < n; ++i) {
        free(*(cuadradoLatino + i)); // Liberar cada fila
    }
    free(cuadradoLatino); // Liberar el arreglo de filas
    free(numeros);        // Liberar los números
}

// Función para leer un número entero
int CuadradoLatino::leerEntero(const std::string& mensaje) {
    int valor = 0;
    char tecla;
    bool numeroIngresado = false;

    std::cout << mensaje;

    while (true) {
        tecla = _getch();  // Captura la tecla sin mostrarla en pantalla

        if (tecla >= '0' && tecla <= '9') {
            std::cout << tecla;
            valor = valor * 10 + (tecla - '0');
            numeroIngresado = true;
        } else if (tecla == '\r' && numeroIngresado) {
            std::cout << std::endl;
            return valor;
        } else if (tecla == '\b' && numeroIngresado) {
            std::cout << "\b \b";  // Borra el último carácter en pantalla
            valor /= 10;  // Elimina el último dígito
            if (valor == 0) {
                numeroIngresado = false;
            }
        }
    }
}

// Función recursiva para llenar el cuadrado latino
void CuadradoLatino::llenarCuadrado() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            *(*(cuadradoLatino + i) + j) = *(numeros + ((i + j) % n)); // Asigna el valor al cuadrado
        }
    }
}

// Función recursiva para imprimir el cuadrado latino en la ventana gráfica
void CuadradoLatino::imprimirCuadrado() {
    // Inicializar el modo gráfico
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL); // Cambia "" a la ruta de BGI si es necesario

    // Dimensiones de la ventana
    int ancho = getmaxx();
    int alto = getmaxy();
    int tamanoCuadrado = std::min(ancho, alto) / (n + 1); // Tamaño de cada celda

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x = (j + 1) * tamanoCuadrado; // Espaciado
            int y = (i + 1) * tamanoCuadrado;

            // Dibujar el cuadro
            rectangle(x - tamanoCuadrado / 2, y - tamanoCuadrado / 2,
                      x + tamanoCuadrado / 2, y + tamanoCuadrado / 2);

            // Mostrar el número en el cuadro
            char buffer[10];
            sprintf(buffer, "%d", *(*(cuadradoLatino + i) + j)); // Usar aritmética de punteros
            outtextxy(x - tamanoCuadrado / 4, y - tamanoCuadrado / 4, buffer);
        }
    }

    // Esperar a que el usuario presione una tecla
    getch();

    // Cerrar el modo gráfico
    closegraph();
}

// Función para leer los números
void CuadradoLatino::leerNumeros() {
    std::cout << "Ingrese " << n << " numeros:\n";
    for (int i = 0; i < n; ++i) {
        *(numeros + i) = leerEntero("Numero " + std::to_string(i + 1) + ": ");
    }
}

// Función principal para generar y mostrar el cuadrado latino
void CuadradoLatino::generarCuadrado() {
    leerNumeros();
    llenarCuadrado();
    imprimirCuadrado();
}
