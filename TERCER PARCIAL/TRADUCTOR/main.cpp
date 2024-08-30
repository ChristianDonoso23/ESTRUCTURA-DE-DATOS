#include "Imagenes.cpp"
#include "Traductor.cpp"
#include <iostream>
#include <string>
#include <conio.h>
#include <cctype>
#include <thread>
#include <chrono>
using namespace std;
std::string obtenerPalabra() {
    std::string entrada;
    char tecla;
    std::cout << "Ingrese una palabra en espanol: ";
    while (true) {
        tecla = _getch();
        if (tecla == 13 && !entrada.empty()) {  // Enter presionado
            std::cout << std::endl;
            return entrada;
        }
        if (isalpha(tecla)) {  // Solo permite letras
            entrada += tecla;
            std::cout << tecla;
        } else if (tecla == 8 && !entrada.empty()) {  // Manejo de retroceso
            entrada.pop_back();
            std::cout << "\b \b";
        }
    }
}

int main() {
    Traductor traductor;

    while (true) {
        // Obtener palabra solo con letras
        cout << "TRADUCTOR DE PALABRAS ESPANOL A INGLES" << endl;
        std::string word = obtenerPalabra();
        // Traducir palabra
        std::string translatedWord = traductor.translateWord(word);
        if (!translatedWord.empty()) {
            std::cout << "Palabra traducida: " << translatedWord << std::endl;
        } else {
            std::cerr << "Error en la traduccion." << std::endl;
            continue;
        }

        // Buscar imagen usando la palabra ingresada en español
        std::string apiKey = "AtWaXDORGIBIwlBOLgF1o88d_5Cq9hrNsKA9atcAJTI";
        std::string searchUrl = "https://api.unsplash.com/search/photos?query=" + word + "&client_id=" + apiKey + "&per_page=1";
        std::string jsonResponse = getJsonResponse(searchUrl);

        std::string imageUrl = extractImageUrl(jsonResponse);
        if (imageUrl.empty()) {
            std::cerr << "No se encontró la URL de la imagen en la respuesta JSON." << std::endl;
            continue;
        }

        std::string downloadedImageFileName = "downloaded_image.jpg";
        downloadImage(imageUrl, downloadedImageFileName);

        std::string bmpImageFileName = "downloaded_image.bmp";
        convertToBmp(downloadedImageFileName, bmpImageFileName);

        std::cout << "Imagen descargada y guardada como " << bmpImageFileName << std::endl;

        // Descargar el audio de la palabra traducida
        std::string audioFileName = "translated_audio";
        descargarAudioTTS(translatedWord, audioFileName);

        std::string command = "start " + audioFileName + ".mp3";
        system(command.c_str());

        displayImageWithGraphics(bmpImageFileName, word);

        closegraph();

        std::cout << "Presione 'Esc' para salir o cualquier otra tecla para continuar..." << std::endl;
        char tecla = _getch();
        if (tecla == 27) {  // 27 es el código ASCII para la tecla Esc
            break;
        }
        system("cls");
    }

    return 0;
}
