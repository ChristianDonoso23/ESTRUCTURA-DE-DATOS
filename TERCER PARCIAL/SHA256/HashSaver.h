#ifndef HASHSAVER_H
#define HASHSAVER_H

#include <string>
using namespace std;
class HashSaver {
public:
    void saveHashToFile(const string& hash, const string& outputFilename);
};

#endif
