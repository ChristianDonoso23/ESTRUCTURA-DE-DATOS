#include <iostream>
#include <fstream>
#include <regex>
#include <stack>
#include <graphics.h>
#include <cmath>
#include <chrono>

// Escalado para ajustar las curvas en la ventana gráfica
int scaleX(int x) { return 50 + x * 5; }  // Ajuste de la escala X para el rango 0 a 100
int scaleY(double y) { return 450 - y * 0.9; }  // Ajuste de la escala Y para el rango 0 a 500

// Función factorial para O(n!)
double factorial(int n) {
    double result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// Funciones para graficar diferentes notaciones Big O
void drawAxes() {
    // Dibujar eje X
    line(50, 450, 550, 450);  // Eje X desde (50, 450) hasta (550, 450)
    // Dibujar eje Y
    line(50, 450, 50, 50);    // Eje Y desde (50, 450) hasta (50, 50)

    // Dibujar divisiones en el eje X
    for (int i = 0; i <= 100; i += 10) {
        int x = scaleX(i);
        line(x, 450, x, 455);  // Marca pequeña en el eje X
        char label[10];
        sprintf(label, "%d", i);
        outtextxy(x - 10, 460, label);  // Etiqueta en el eje X
    }

    // Dibujar divisiones en el eje Y
    for (int i = 0; i <= 500; i += 100) {
        int y = scaleY(i);
        line(45, y, 50, y);  // Marca pequeña en el eje Y
        char label[10];
        sprintf(label, "%d", i);
        outtextxy(10, y - 5, label);  // Etiqueta en el eje Y
    }
}

void drawO1() {
    int prevX = scaleX(0);
    int prevY = scaleY(1);
    for (int n = 1; n <= 100; ++n) {
        int currX = scaleX(n);
        int currY = scaleY(1);  // O(1) es constante
        line(prevX, prevY, currX, currY);
        prevX = currX;
        prevY = currY;
    }
}

void drawOlogN() {
    int prevX = scaleX(1);
    int prevY = scaleY(log2(1));
    for (int n = 2; n <= 100; ++n) {
        int currX = scaleX(n);
        int currY = scaleY(log2(n));
        line(prevX, prevY, currX, currY);
        prevX = currX;
        prevY = currY;
    }
}

void drawOn() {
    int prevX = scaleX(0);
    int prevY = scaleY(0);
    for (int n = 1; n <= 100; ++n) {
        int currX = scaleX(n);
        int currY = scaleY(n);
        line(prevX, prevY, currX, currY);
        prevX = currX;
        prevY = currY;
    }
}

void drawONlogN() {
    int prevX = scaleX(1);
    int prevY = scaleY(1 * log2(1));
    for (int n = 2; n <= 100; ++n) {
        int currX = scaleX(n);
        int currY = scaleY(n * log2(n));
        line(prevX, prevY, currX, currY);
        prevX = currX;
        prevY = currY;
    }
}

void drawOnSquared() {
    int prevX = scaleX(0);
    int prevY = scaleY(0);
    for (int n = 1; n <= 100; ++n) {
        int currX = scaleX(n);
        int currY = scaleY(n * n);
        line(prevX, prevY, currX, currY);
        prevX = currX;
        prevY = currY;
    }
}

void drawO2n() {
    int prevX = scaleX(0);
    int prevY = scaleY(0);
    for (int n = 1; n <= 15; ++n) { // Limitado a 15 para evitar valores demasiado grandes
        int currX = scaleX(n);
        int currY = scaleY(pow(2, n));
        line(prevX, prevY, currX, currY);
        prevX = currX;
        prevY = currY;
    }
}

void drawONfactorial() {
    int prevX = scaleX(0);
    int prevY = scaleY(1);
    for (int n = 1; n <= 10; ++n) { // Limitado a 10 para evitar valores demasiado grandes
        int currX = scaleX(n);
        int currY = scaleY(factorial(n));
        line(prevX, prevY, currX, currY);
        prevX = currX;
        prevY = currY;
    }
}

std::string analizarNotacionBigO(const std::string& archivo) {
    std::ifstream file(archivo);
    if (!file.is_open()) {
        return "Error: No se puede abrir el archivo.";
    }

    std::string line;
    std::stack<int> bucles;
    int maxProfundidad = 0;
    bool tieneLogN = false;
    bool tieneNLogN = false;
    bool tieneCuadratica = false;
    bool tieneExponecial = false;
    bool tieneFactorial = false;
    bool tieneRecursion = false;
    
    std::regex recursionPattern("([a-zA-Z_][a-zA-Z0-9_]*)\\s*\\(");

    while (std::getline(file, line)) {
        line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));
        line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);

        // Manejo de bucles for y while
        if (line.find("for") != std::string::npos || line.find("while") != std::string::npos) {
            bucles.push(1);
            if (bucles.size() > maxProfundidad) {
                maxProfundidad = bucles.size();
            }
        }

        if (line.find("}") != std::string::npos) {
            if (!bucles.empty()) {
                bucles.pop();
            }
        }

        // Detección de log n
        if (line.find("log") != std::string::npos) {
            tieneLogN = true;
        }

        // Detección de llamadas recursivas
        if (line.find("return") != std::string::npos && std::regex_search(line, recursionPattern)) {
            tieneRecursion = true;
        }
    }

    file.close();

    // Determinación de la notación Big O
    if (tieneRecursion) {
        if (maxProfundidad > 1) {
            return "O(2^n)";
        } else {
            return "O(n!)"; // Asumimos recursión factorial si no hay profundidad mayor
        }
    } else if (tieneLogN && maxProfundidad == 1) {
        return "O(log n)";
    } else if (maxProfundidad == 2) {
        return "O(n^2)";
    } else if (tieneLogN && maxProfundidad > 1) {
        return "O(n log n)";
    } else if (maxProfundidad == 1) {
        return "O(n)";
    } else {
        return "O(1)"; // Suponemos constante si no hay bucles detectados
    }
}

// Función para medir el tiempo de ejecución
template<typename Func, typename... Args>
auto medir_tiempo(Func&& func, Args&&... args) {
    auto inicio = std::chrono::high_resolution_clock::now();  // Tiempo de inicio
    auto resultado = func(std::forward<Args>(args)...);  // Ejecutar la función
    auto fin = std::chrono::high_resolution_clock::now();  // Tiempo de finalización

    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio).count();
    std::cout << "Tiempo de ejecución: " << duracion << " ms" << std::endl;

    return resultado;  // Devolver el resultado de la función
}

// Función de ejemplo para medir el tiempo de ejecución
int funcion_a_medir(int n) {
    int suma = 0;
    for (int i = 0; i < n; ++i) {
        suma += i;
    }
    return suma;
}

int main() {
    // Inicializar la ventana gráfica
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    std::string archivo = "codigo.txt"; // Nombre del archivo con el código
    std::string notacion = analizarNotacionBigO(archivo);

    std::cout << "Notación Big O detectada: " << notacion << std::endl;

    // Medir el tiempo de ejecución de la función en el archivo
    int resultado = medir_tiempo(funcion_a_medir, 1000000);
    std::cout << "Resultado de la función: " << resultado << std::endl;

    // Configurar la ventana gráfica y dibujar
    setcolor(WHITE);
    drawAxes();

    if (notacion == "O(1)") {
        drawO1();
    } else if (notacion == "O(log n)") {
        drawOlogN();
    } else if (notacion == "O(n)") {
        drawOn();
    } else if (notacion == "O(n log n)") {
        drawONlogN();
    } else if (notacion == "O(n^2)") {
        drawOnSquared();
    } else if (notacion == "O(2^n)") {
        drawO2n();
    } else if (notacion == "O(n!)") {
        drawONfactorial();
    }

    getch();

    closegraph(); // Cierra la ventana gráfica

    return 0;
}
