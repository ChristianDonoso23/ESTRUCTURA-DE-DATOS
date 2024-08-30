#include "Traductor.h"
#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <sstream>

#pragma comment(lib, "wininet.lib")

Traductor::Traductor() {
}

Traductor::~Traductor() {
}

std::string Traductor::translateWord(const std::string& word) {
    std::string apiUrl = "api.mymemory.translated.net";
    std::string query = "/get?q=" + word + "&langpair=es|en";

    HINTERNET hInternet = InternetOpen(TEXT("Translation Client"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL) {
        std::cerr << "InternetOpen failed: " << GetLastError() << std::endl;
        return "";
    }

    HINTERNET hConnect = InternetConnect(hInternet, apiUrl.c_str(), INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    if (hConnect == NULL) {
        std::cerr << "InternetConnect failed: " << GetLastError() << std::endl;
        InternetCloseHandle(hInternet);
        return "";
    }

    HINTERNET hRequest = HttpOpenRequest(hConnect, "GET", query.c_str(), NULL, NULL, NULL, 0, 0);
    if (hRequest == NULL) {
        std::cerr << "HttpOpenRequest failed: " << GetLastError() << std::endl;
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return "";
    }

    BOOL sent = HttpSendRequest(hRequest, NULL, 0, NULL, 0);
    if (!sent) {
        std::cerr << "HttpSendRequest failed: " << GetLastError() << std::endl;
        InternetCloseHandle(hRequest);
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return "";
    }

    std::string response;
    char buffer[4096];
    DWORD bytesRead;
    while (InternetReadFile(hRequest, buffer, sizeof(buffer) - 1, &bytesRead) && bytesRead > 0) {
        buffer[bytesRead] = '\0';
        response.append(buffer);
    }

    InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    std::string translatedTextKey = "\"translatedText\":\"";
    size_t startPos = response.find(translatedTextKey);
    if (startPos == std::string::npos) {
        std::cerr << "No se encontró la clave 'translatedText' en la respuesta." << std::endl;
        return "";
    }

    startPos += translatedTextKey.length();
    size_t endPos = response.find("\"", startPos);
    if (endPos == std::string::npos) {
        std::cerr << "No se encontró el final de la cadena de traducción." << std::endl;
        return "";
    }

    return response.substr(startPos, endPos - startPos);
}
