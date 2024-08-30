#include "Laberinto.cpp"
#include "Interfaz.cpp"
#include "Juego.cpp"
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(0)); // Inicializar la semilla para números aleatorios

    int opcion;
    string nombreArchivo = "laberinto.txt";
    int ancho, alto;

    do {
        Interfaz::mostrarMenu(opcion);

        switch (opcion) {
            case 1: {
                // Obtener el ancho del laberinto
                ancho = Interfaz::obtenerNumeroConMensaje("Ingrese el ancho del laberinto (entre 15 y 30): ", 15, 30);
                // Obtener el alto del laberinto
                alto = Interfaz::obtenerNumeroConMensaje("Ingrese el alto del laberinto (entre 15 y 30): ", 15, 30);

                // Crear el laberinto y colocar la salida en la esquina inferior derecha
                Laberinto laberinto(ancho, alto);
                laberinto.colocarSalida();

                // Guardar el laberinto en un archivo
                laberinto.guardarEnArchivo(nombreArchivo);
                cout << "Laberinto generado y guardado en " << nombreArchivo << ". Presiona cualquier tecla para continuar..." << endl;
                _getch(); // Esperar que el usuario presione una tecla
                break;
            }
            case 2: {
                // Leer el laberinto desde el archivo
                Laberinto* laberinto = Laberinto::leerDesdeArchivo(nombreArchivo, ancho, alto);
                if (laberinto != nullptr) {
                    // Jugar el laberinto
                    Juego::jugarLaberinto(laberinto, ancho, alto);

                    delete laberinto;
                }
                break;
            }
            case 3:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción inválida. Intenta nuevamente." << endl;
                break;
        }
    } while (opcion != 3);

    return 0;
}
