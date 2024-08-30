#include <graphics.h>
#include <iostream>
#include <conio.h>
#include "JuegoHanoi.cpp"

using namespace std;

int leerEntero(const string& mensaje);

int main() {
    int numDiscos, numTorres;
    char opcion;

    do {
        // Solicitar número de discos con validación
        numDiscos = leerEntero("Ingrese el numero de discos (debe ser mayor o igual a 3): ");
        while (numDiscos < 3) {
            numDiscos = leerEntero("El numero de discos debe ser mayor o igual a 3. Intente nuevamente: ");
        }

        // Solicitar número de torres con validación
        numTorres = leerEntero("Ingrese el numero de torres (debe ser mayor o igual al numero de discos): ");
        while (numTorres < numDiscos) {
            numTorres = leerEntero("El numero de torres debe ser mayor o igual al numero de discos. Intente nuevamente: ");
        }

        // Elegir torres de origen y destino
        int torreOrigen, torreDestino;
        torreOrigen = leerEntero("Elija la torre de origen (1-" + to_string(numTorres) + "): ");
        while (torreOrigen < 1 || torreOrigen > numTorres) {
            torreOrigen = leerEntero("Torre no valida. Elija una torre de origen valida (1-" + to_string(numTorres) + "): ");
        }

        torreDestino = leerEntero("Elija la torre de destino (1-" + to_string(numTorres) + "): ");
        while (torreDestino < 1 || torreDestino > numTorres || torreDestino == torreOrigen) {
            torreDestino = leerEntero("Torre no valida. Elija una torre de destino valida (1-" + to_string(numTorres) + "), diferente de la torre de origen: ");
        }

        int gd = DETECT, gm;
        int width = 1000;
        int height = 600;
        initwindow(width, height, "Torres de Hanoi");

        JuegoHanoi juego(numDiscos, numTorres, torreOrigen - 1);

        // Selección de la torre auxiliar para la recursión
        int torreAuxiliar;
        for (int i = 0; i < numTorres; ++i) {
            if (i != torreOrigen - 1 && i != torreDestino - 1) {
                torreAuxiliar = i;
                break;
            }
        }

        // Mover todos los discos recursivamente de la torre de origen a la torre de destino
        juego.moverDiscos(numDiscos, torreOrigen - 1, torreDestino - 1, torreAuxiliar);

        // Pausar la ejecución para que puedas ver el resultado final
        cout << "Presiona cualquier tecla para cerrar la ventana grafica y continuar..." << endl;
        getch();

        // Cerrar el modo gráfico
        closegraph();

        // Preguntar al usuario si desea continuar
        cout << "Desea ingresar nuevos datos y resolver otra configuracion (s/n): ";
        opcion = _getch(); // Captura la opción sin mostrarla
        cout << opcion << endl;

    } while (opcion == 's' || opcion == 'S');

    cout << "Gracias por usar el programa. ¡Adios!" << endl;
    return 0;
}

int leerEntero(const string& mensaje) {
    int valor = 0;
    char tecla;
    bool numeroIngresado = false;

    cout << mensaje;

    while (true) {
        tecla = _getch();  // Captura la tecla sin mostrarla en pantalla

        if (tecla >= '0' && tecla <= '9') {
            // Si la tecla es un número, muéstralo y añádelo al valor
            cout << tecla;
            valor = valor * 10 + (tecla - '0');
            numeroIngresado = true;
        } else if (tecla == '\r' && numeroIngresado) {
            // Si se presiona Enter y se ha ingresado al menos un número, retorna el valor
            cout << endl;
            return valor;
        } else if (tecla == '\b' && numeroIngresado) {
            // Si se presiona Backspace y hay algo para borrar
            cout << "\b \b";  // Borra el último carácter en pantalla
            valor /= 10;  // Elimina el último dígito
            if (valor == 0) {
                numeroIngresado = false;
            }
        }
    }
}
