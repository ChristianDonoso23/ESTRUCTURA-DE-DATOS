#ifndef TRADUCTOR_H
#define TRADUCTOR_H

#include <string>

class Traductor {
public:
    Traductor();  // Constructor
    ~Traductor(); // Destructor

    std::string translateWord(const std::string& word);
};

#endif // TRADUCTOR_H
