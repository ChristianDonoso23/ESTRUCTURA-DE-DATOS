#include <iostream>
#include <conio.h>
#include "CuboMagico.cpp"

using namespace std;

void mostrarMenu(int opcionSeleccionada) {
    system("cls");
    cout << "Menu de seleccion:" << endl;
    
    for (int i = 1; i <= 4; ++i) {
        if (i == opcionSeleccionada) {
            cout << "> ";
        } else {
            cout << "  ";
        }

        switch (i) {
            case 1:
                cout << "Mostrar cuadrado magico de numeros impares" << endl;
                break;
            case 2:
                cout << "Mostrar cuadrado magico de numeros pares" << endl;
                break;
            case 3:
                cout << "Mostrar cuadrado magico tradicional" << endl;
                break;
            case 4:
                cout << "Salir" << endl;
                break;
        }
    }
}

int capturarNumero() {
    int numero = 0;
    char tecla;
    
    while (true) {
        tecla = _getch();
        
        if (tecla >= '0' && tecla <= '9') {
            cout << tecla;
            numero = numero * 10 + (tecla - '0');
        } else if (tecla == '\r') {
            cout << endl;
            break;
        } else if (tecla == '\b' && numero > 0) {
            cout << "\b \b";
            numero /= 10;
        }
    }
    
    return numero;
}

int main() {
    int n = 3;
    int opcion = 1;
    int tecla;

    while (true) {
        mostrarMenu(opcion);
        
        tecla = _getch();
        
        if (tecla == 0 || tecla == 224) {
            tecla = _getch();
            switch (tecla) {
                case 72:
                    opcion = (opcion == 1) ? 4 : opcion - 1;
                    break;
                case 80:
                    opcion = (opcion == 4) ? 1 : opcion + 1;
                    break;
            }
        } else if (tecla == '\r') {
            if (opcion == 4) {
                cout << "Saliendo del programa..." << endl;
                break;
            } else {
                int gd = DETECT, gm;
                initgraph(&gd, &gm, NULL);
                
                CuadradoMagico cuadradoMagico(n, opcion == 1, 100, 100);
                
                if (opcion == 3) {
                    int numero_inicial, incremento;
                    cout << "Ingrese el numero inicial: ";
                    numero_inicial = capturarNumero();
                    cout << "Ingrese el incremento: ";
                    incremento = capturarNumero();
                    
                    cuadradoMagico.llenarCuadradoMagicoTradicional(numero_inicial, incremento);
                } else {
                    cuadradoMagico.dibujar();
                }
                
                cout << "Presiona la tecla Espacio para cerrar la ventana grafica...";
                while (_getch() != ' ') {}
                closegraph();
            }
        }
    }
    return 0;
}
