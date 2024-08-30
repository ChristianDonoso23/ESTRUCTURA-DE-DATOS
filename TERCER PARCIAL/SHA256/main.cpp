#include "FileHasher.cpp"
#include "HashSaver.cpp"
#include <iostream>
using namespace std;
int main() {
    string filename = "documento.txt";
    FileHasher fileHasher;
    string hash = fileHasher.hashFile(filename);
    
    if (!hash.empty()) {
        HashSaver hashSaver;
        string outputFilename = "documento_hash.txt";
        hashSaver.saveHashToFile(hash, outputFilename);
    }

    cout << "Presiona enter para salir...";
    cin.get();

    return 0;
}
