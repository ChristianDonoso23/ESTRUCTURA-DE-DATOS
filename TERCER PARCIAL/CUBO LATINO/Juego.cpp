#include <graphics.h>
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <limits>

// Función para leer un número entero
int leerEntero(const std::string& mensaje) {
    int valor = 0;
    char tecla;
    bool numeroIngresado = false;

    std::cout << mensaje;

    while (true) {
        tecla = _getch();  // Captura la tecla sin mostrarla en pantalla

        if (tecla >= '0' && tecla <= '9') {
            // Si la tecla es un número, muéstralo y añádelo al valor
            std::cout << tecla;
            valor = valor * 10 + (tecla - '0');
            numeroIngresado = true;
        } else if (tecla == '\r' && numeroIngresado) {
            // Si se presiona Enter y se ha ingresado al menos un número, retorna el valor
            std::cout << std::endl;
            return valor;
        } else if (tecla == '\b' && numeroIngresado) {
            // Si se presiona Backspace y hay algo para borrar
            std::cout << "\b \b";  // Borra el último carácter en pantalla
            valor /= 10;  // Elimina el último dígito
            if (valor == 0) {
                numeroIngresado = false;
            }
        }
    }
}

// Función recursiva para llenar el cuadrado latino
void llenarCuadradoLatino(int** cuadradoLatino, int* numeros, int n, int i, int j) {
    if (i >= n) return; // Si se ha llenado toda la fila, termina

    *(*(cuadradoLatino + i) + j) = *(numeros + ((i + j) % n)); // Asigna el valor al cuadrado

    if (j + 1 < n) {
        llenarCuadradoLatino(cuadradoLatino, numeros, n, i, j + 1); // Llama a la siguiente columna
    } else {
        llenarCuadradoLatino(cuadradoLatino, numeros, n, i + 1, 0); // Llama a la siguiente fila
    }
}

// Función recursiva para imprimir el cuadrado latino en la ventana gráfica
void imprimirCuadradoLatino(int** cuadradoLatino, int n, int i, int j, int tamanoCuadrado) {
    if (i >= n) return; // Si se ha impreso toda la fila, termina

    int x = (j + 1) * tamanoCuadrado; // Espaciado
    int y = (i + 1) * tamanoCuadrado;

    // Dibujar el cuadro
    rectangle(x - tamanoCuadrado / 2, y - tamanoCuadrado / 2,
              x + tamanoCuadrado / 2, y + tamanoCuadrado / 2);

    // Mostrar el número en el cuadro
    char buffer[10];
    sprintf(buffer, "%d", *(*(cuadradoLatino + i) + j)); // Usar aritmética de punteros
    outtextxy(x - tamanoCuadrado / 4, y - tamanoCuadrado / 4, buffer);

    if (j + 1 < n) {
        imprimirCuadradoLatino(cuadradoLatino, n, i, j + 1, tamanoCuadrado); // Llama a la siguiente columna
    } else {
        imprimirCuadradoLatino(cuadradoLatino, n, i + 1, 0, tamanoCuadrado); // Llama a la siguiente fila
    }
}

void generarCuadradoLatino(int n, int* numeros) {
    // Asignar memoria dinámica para el cuadrado latino
    int** cuadradoLatino = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        *(cuadradoLatino + i) = (int*)malloc(n * sizeof(int));
    }

    // Llenar el cuadrado latino de forma recursiva
    llenarCuadradoLatino(cuadradoLatino, numeros, n, 0, 0);

    // Inicializar el modo gráfico
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL); // Cambia "" a la ruta de BGI si es necesario

    // Dimensiones de la ventana
    int ancho = getmaxx();
    int alto = getmaxy();
    int tamanoCuadrado = std::min(ancho, alto) / (n + 1); // Tamaño de cada celda

    // Imprimir el cuadrado latino de forma recursiva
    imprimirCuadradoLatino(cuadradoLatino, n, 0, 0, tamanoCuadrado);

    // Esperar a que el usuario presione una tecla
    getch();

    // Liberar la memoria asignada
    for (int i = 0; i < n; ++i) {
        free(*(cuadradoLatino + i)); // Liberar cada fila
    }
    free(cuadradoLatino); // Liberar el arreglo de filas

    // Cerrar el modo gráfico
    closegraph();
}

int main() {
    int n;
    n = leerEntero("Ingrese el orden del cuadrado latino (n): ");

    // Verificar que n sea mayor que 0
    if (n < 1) {
        std::cout << "El orden debe ser mayor que 0." << std::endl;
        return 1;
    }

    // Asignar memoria dinámica para los números ingresados
    int* numeros = (int*)malloc(n * sizeof(int));

    // Ingresar los n números que se usarán en el cuadrado latino
    std::cout << "Ingrese " << n << " numeros:\n";
    for (int i = 0; i < n; ++i) {
        *(numeros + i) = leerEntero("Numero " + std::to_string(i + 1) + ": ");
    }

    generarCuadradoLatino(n, numeros);

    // Liberar la memoria asignada para los números
    free(numeros);

    return 0;
}
