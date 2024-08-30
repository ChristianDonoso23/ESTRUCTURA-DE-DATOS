#include "Imagenes.h"
#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <graphics.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "wininet.lib")


// Función para obtener la respuesta JSON de una URL
std::string getJsonResponse(const std::string& url) {
    HINTERNET hInternet = InternetOpen(TEXT("API Client"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL) {
        std::cerr << "InternetOpen failed: " << GetLastError() << std::endl;
        return "";
    }

    HINTERNET hConnect = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (hConnect == NULL) {
        std::cerr << "InternetOpenUrlA failed: " << GetLastError() << std::endl;
        InternetCloseHandle(hInternet);
        return "";
    }

    std::string response;
    char buffer[4096];
    DWORD bytesRead;
    while (InternetReadFile(hConnect, buffer, sizeof(buffer) - 1, &bytesRead) && bytesRead > 0) {
        buffer[bytesRead] = '\0';
        response.append(buffer);
    }

    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);
    return response;
}

// Función para extraer la URL de la imagen del JSON
std::string extractImageUrl(const std::string& json) {
    size_t startPos = json.find("\"regular\":\"");
    if (startPos == std::string::npos) return "";

    startPos += 11; // Length of "\"regular\":\""
    size_t endPos = json.find("\"", startPos);
    if (endPos == std::string::npos) return "";

    return json.substr(startPos, endPos - startPos);
}

// Función para descargar la imagen desde una URL
void downloadImage(const std::string& imageUrl, const std::string& outputFileName) {
    HINTERNET hInternet = InternetOpen(TEXT("Image Downloader"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL) {
        std::cerr << "InternetOpen failed: " << GetLastError() << std::endl;
        return;
    }

    HINTERNET hImage = InternetOpenUrlA(hInternet, imageUrl.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (hImage == NULL) {
        std::cerr << "InternetOpenUrlA (image) failed: " << GetLastError() << std::endl;
        InternetCloseHandle(hInternet);
        return;
    }

    std::ofstream outFile(outputFileName, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error al abrir el archivo para escribir." << std::endl;
        InternetCloseHandle(hImage);
        InternetCloseHandle(hInternet);
        return;
    }

    char buffer[4096];
    DWORD bytesRead;
    while (InternetReadFile(hImage, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        outFile.write(buffer, bytesRead);
    }

    outFile.close();
    InternetCloseHandle(hImage);
    InternetCloseHandle(hInternet);
}

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

// Función para convertir una imagen a BMP
void convertToBmp(const std::string& inputFileName, const std::string& outputFileName) {
    int width, height, channels;
    unsigned char* imgData = stbi_load(inputFileName.c_str(), &width, &height, &channels, 0);
    if (imgData == nullptr) {
        std::cerr << "Error al cargar la imagen: " << stbi_failure_reason() << std::endl;
        return;
    }

    // Convertir a BMP
    stbi_write_bmp(outputFileName.c_str(), width, height, channels, imgData);

    stbi_image_free(imgData);
}

// Función principal para mostrar la ventana gráfica
void displayImageWithGraphics(const std::string& imageFileName, const std::string& title) {
    int winWidth = 800;
    int winHeight = 600;
    initwindow(winWidth, winHeight, "Imagenes");
    setbkcolor(WHITE);

    setcolor(BLACK);
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    outtextxy(10, 10, const_cast<char*>(title.c_str()));
    int imgWidth = 400; 
    int imgHeight = 400; 

    // Calcular las coordenadas para centrar la imagen
    int x = (winWidth - imgWidth) / 2;
    int y = (winHeight - imgHeight) / 2;

    // Dibujar un borde negro alrededor de la ventana
    setcolor(BLACK);
    rectangle(0, 0, winWidth - 1, winHeight - 1);

    // Mostrar la imagen centrada con el tamaño reducido
    dibujarImagenBMP(x, y, imageFileName.c_str());

    // Mantener la ventana abierta
    getch();
    closegraph();
}

void dibujarImagenBMP(int x, int y, const char* archivo) {
    // Cargar la imagen y dibujarla con las nuevas dimensiones
    readimagefile(archivo, x, y, x + 400, y + 400); // Reducción de la imagen
}

void descargarAudioTTS(const std::string& texto, std::string outputFileName) {
    if (outputFileName.find(".mp3") == std::string::npos) {
        outputFileName += ".mp3";
    }
    std::string apiUrl = "https://translate.google.com/translate_tts?ie=UTF-8&client=tw-ob&q=" + texto + "&tl=en";
    downloadImage(apiUrl, outputFileName);  // Guardar como MP3
}

