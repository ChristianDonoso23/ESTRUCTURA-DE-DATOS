#include "FileHasher.h"
#include "SHA256.cpp"
#include <fstream>
#include <sstream>
#include <iostream>

string FileHasher::hashFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "No se pudo abrir el archivo: " << filename << endl;
        return "";
    }
    
    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();
    
    SHA256 sha256;
    return sha256.hash(content);
}
