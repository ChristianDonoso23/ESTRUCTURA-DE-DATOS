#ifndef SHA256_H
#define SHA256_H

#include <string>
#include <cstdint>
using namespace std;
class SHA256 {
public:
    SHA256();
    string hash(const string& input);

private:
    uint32_t rotr(uint32_t n, unsigned int c);
    uint32_t choose(uint32_t e, uint32_t f, uint32_t g);
    uint32_t majority(uint32_t a, uint32_t b, uint32_t c);
    uint32_t sigma0(uint32_t x);
    uint32_t sigma1(uint32_t x);
    uint32_t gamma0(uint32_t x);
    uint32_t gamma1(uint32_t x);

    uint8_t* padMessage(const uint8_t* message, size_t originalLength, size_t& paddedSize);
    void transform(uint32_t* state, const uint8_t* block);

    static const uint32_t k[64];
};

#endif
