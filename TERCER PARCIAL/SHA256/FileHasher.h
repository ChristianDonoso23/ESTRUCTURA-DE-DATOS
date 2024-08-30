#ifndef FILEHASHER_H
#define FILEHASHER_H

#include <string>
using namespace std;
class FileHasher {
public:
    string hashFile(const string& filename);
};

#endif
