#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <conio.h>

using namespace std;

int obtenerCodigo(const string& mensaje) {
    string entrada;
    char tecla;
    
    cout << mensaje;
    while (true) {
        tecla = _getch();

        if (tecla == 27) {
            cout << "\nPrograma terminado por el usuario." << endl;
            exit(0);
        }

        if (tecla == 13 && entrada.length() == 3) {
            cout << endl;
            return stoi(entrada);
        }
        
        if ((tecla == '1' || tecla == '2' || tecla == '3') && entrada.length() < 3) {
            entrada += tecla;
            cout << tecla;
        } else if (tecla == 8 && !entrada.empty()) {
            entrada.pop_back();
            cout << "\b \b";
        }
    }
}

void generarCodigoAleatorioRecursivo(int* codigo, int n, int indice = 0) {
    if (indice == n) {
        return;
    }
    codigo[indice] = rand() % 3 + 1;
    generarCodigoAleatorioRecursivo(codigo, n, indice + 1);
}

int* generarCodigoAleatorio(int n) {
    int* codigo = new int[n];
    generarCodigoAleatorioRecursivo(codigo, n);
    return codigo;
}

int convertirCodigoAEntero(int* codigo, int n) {
    int codigoEntero = 0;
    for (int i = 0; i < n; ++i) {
        codigoEntero = codigoEntero * 10 + codigo[i];
    }
    return codigoEntero;
}

void guardarCodigoEnArchivo(int* codigo, int n, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        int codigoEntero = convertirCodigoAEntero(codigo, n);
        archivo << codigoEntero;
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo para guardar el codigo." << endl;
    }
}

bool verificarCodigo(int* codigoCorrecto, int n) {
    int intento = obtenerCodigo("Ingresa el codigo de 3 digitos (solo 1, 2, 3): ");
    int codigoCorrectoEntero = convertirCodigoAEntero(codigoCorrecto, n);
    return intento == codigoCorrectoEntero;
}

int main() {
    srand(time(0));
    int n = 3;

    int* codigo = generarCodigoAleatorio(n);

    guardarCodigoEnArchivo(codigo, n, "codigo_correcto.txt");

    cout << "Un codigo aleatorio ha sido generado. Intenta adivinarlo." << endl;

    while (true) {
        if (verificarCodigo(codigo, n)) {
            cout << "Felicidades, has ingresado el codigo correcto." << endl;
            
            cout << "Presiona Enter para intentar con un nuevo codigo o Escape para salir." << endl;
            char tecla = _getch();

            if (tecla == 27) {
                cout << "Programa terminado por el usuario." << endl;
                delete[] codigo;
                exit(0);
            } else if (tecla == 13) {
                delete[] codigo;
                codigo = generarCodigoAleatorio(n);
                guardarCodigoEnArchivo(codigo, n, "codigo_correcto.txt");
                cout << "Se ha generado un nuevo codigo. Intenta adivinarlo." << endl;
            }
        } else {
            cout << "Codigo incorrecto. Intentalo de nuevo." << endl;
        }
    }

    delete[] codigo;
    return 0;
}
