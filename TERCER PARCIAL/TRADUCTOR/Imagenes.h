#ifndef IMAGENES_H
#define IMAGENES_H

#include <string>

    // Obtiene la respuesta JSON de una URL
    std::string getJsonResponse(const std::string& url);

    // Extrae la URL de la imagen del JSON
    std::string extractImageUrl(const std::string& json);

    // Descarga la imagen desde una URL
    void downloadImage(const std::string& imageUrl, const std::string& outputFileName);

    // Convierte una imagen a formato BMP
    void convertToBmp(const std::string& inputFileName, const std::string& outputFileName);

    // Muestra una imagen en una ventana gráfica
    void displayImageWithGraphics(const std::string& imageFileName, const std::string& title);

    void dibujarImagenBMP(int x, int y, const char* archivo);

    void descargarAudioTTS(const std::string& texto, std::string outputFileName);
    
#endif // IMAGENES_H
