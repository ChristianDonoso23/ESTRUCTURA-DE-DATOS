#include <iostream>
#include <graphics.h>
#include <conio.h>  // Para usar _getch()
#include "ArbolExpresion.cpp"

using namespace std;

// Función para leer la expresión, permitiendo solo números, operadores, paréntesis, ciertas letras y espacios
string leerExpresion(const string& mensaje) {
    string expresion;
    char tecla;
    bool numeroIngresado = false;

    cout << mensaje;

    while (true) {
        tecla = _getch();  // Captura la tecla sin mostrarla en pantalla

        // Permitir dígitos, operadores básicos, paréntesis, ciertas letras y espacios
        if ((tecla >= '0' && tecla <= '9') || tecla == '+' || tecla == '-' || tecla == '*' || 
            tecla == '/' || tecla == '(' || tecla == ')' || tecla == ' ' ||
            tecla == 's' || tecla == 'i' || tecla == 'n' || tecla == 'c' || 
            tecla == 'o' || tecla == 't' || tecla == 'a' || tecla == 'q' || 
            tecla == 'r' || tecla == 'e' || tecla == 'x' || tecla == 'p') {
            cout << tecla;
            expresion += tecla;
            numeroIngresado = true;
        } else if (tecla == '\r' && numeroIngresado) {
            // Si se presiona Enter y se ha ingresado al menos un carácter, retorna la expresión
            cout << endl;
            return expresion;
        } else if (tecla == '\b' && !expresion.empty()) {
            // Si se presiona Backspace y hay algo para borrar
            cout << "\b \b";  // Borra el último carácter en pantalla
            expresion.pop_back();  // Elimina el último carácter de la expresión
        }
        // Si la tecla es una letra u otro carácter no válido, simplemente se ignora
    }
}

int main() {
    // Usar la función leerExpresion en lugar de getline
    string expresion = leerExpresion("Ingresa una expresion en notacion infija (usa espacios para separar los elementos): ");

    ArbolExpresion arbol;

    if (!arbol.validarInfija(expresion)) {
        cout << "Expresion invalida. Asegurate de que la expresion este correctamente balanceada y contenga solo numeros, operadores y funciones validos." << endl;
        closegraph();
        return 1;
    }

    arbol.construirArbol(expresion);

    string infija = arbol.obtenerInfija(arbol.raiz);
    string sufija = arbol.obtenerSufija(arbol.raiz);
    string prefija = arbol.obtenerPrefija(arbol.raiz);
    double resultado = arbol.evaluarSufija(sufija);

    cout << "Notacion Infija: " << infija << endl;
    cout << "Notacion Sufija: " << sufija << endl;
    cout << "Notacion Prefija: " << prefija << endl;
    cout << "Resultado de la evaluacion: " << resultado << endl;

    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    
    arbol.mostrarArbol(arbol.raiz, getmaxx() / 2, 50, 0);

    getch();
    closegraph();
    return 0;
}
