#include "HashSaver.h"
#include <fstream>
#include <iostream>

void HashSaver::saveHashToFile(const string& hash, const string& outputFilename) {
    ofstream outputFile(outputFilename);
    if (outputFile) {
        outputFile << hash;
        outputFile.close();
        cout << "Hash SHA-256 guardado en: " << outputFilename << endl;
    } else {
        cerr << "No se pudo guardar el archivo: " << outputFilename << endl;
    }
}
