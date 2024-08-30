#include "SHA256.h"
#include <cstring>
#include <sstream>
#include <iomanip>
// Constantes SHA-256
const uint32_t SHA256::k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

SHA256::SHA256() {}

string SHA256::hash(const string& input) {
    size_t paddedSize;
    uint8_t* message = padMessage(reinterpret_cast<const uint8_t*>(input.c_str()), input.size(), paddedSize);
    
    uint32_t state[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };
    
    for (size_t i = 0; i < paddedSize; i += 64) {
        transform(state, message + i);
    }
    
    delete[] message;
    
    ostringstream result;
    for (int i = 0; i < 8; ++i) {
        result << hex << setw(8) << setfill('0') << *(state + i);
    }
    
    return result.str();
}

uint32_t SHA256::rotr(uint32_t n, unsigned int c) {
    return (n >> c) | (n << (32 - c));
}

uint32_t SHA256::choose(uint32_t e, uint32_t f, uint32_t g) {
    return (e & f) ^ (~e & g);
}

uint32_t SHA256::majority(uint32_t a, uint32_t b, uint32_t c) {
    return (a & b) ^ (a & c) ^ (b & c);
}

uint32_t SHA256::sigma0(uint32_t x) {
    return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22);
}

uint32_t SHA256::sigma1(uint32_t x) {
    return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25);
}

uint32_t SHA256::gamma0(uint32_t x) {
    return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);
}

uint32_t SHA256::gamma1(uint32_t x) {
    return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10);
}

uint8_t* SHA256::padMessage(const uint8_t* message, size_t originalLength, size_t& paddedSize) {
    paddedSize = ((originalLength + 8) / 64 + 1) * 64;
    uint8_t* padded = new uint8_t[paddedSize];
    
    memcpy(padded, message, originalLength);
    *(padded + originalLength) = 0x80;
    
    memset(padded + originalLength + 1, 0, paddedSize - originalLength - 9);
    
    uint64_t bitLength = originalLength * 8;
    for (int i = 0; i < 8; ++i) {
        *(padded + paddedSize - 1 - i) = (bitLength >> (i * 8)) & 0xff;
    }
    
    return padded;
}

void SHA256::transform(uint32_t* state, const uint8_t* block) {
    uint32_t* w = new uint32_t[64];
    uint32_t a, b, c, d, e, f, g, h;
    
    for (int i = 0; i < 16; ++i) {
        *(w + i) = (*(block + i * 4) << 24) | (*(block + i * 4 + 1) << 16) | (*(block + i * 4 + 2) << 8) | *(block + i * 4 + 3);
    }
    
    for (int i = 16; i < 64; ++i) {
        *(w + i) = gamma1(*(w + i - 2)) + *(w + i - 7) + gamma0(*(w + i - 15)) + *(w + i - 16);
    }
    
    a = *(state + 0);
    b = *(state + 1);
    c = *(state + 2);
    d = *(state + 3);
    e = *(state + 4);
    f = *(state + 5);
    g = *(state + 6);
    h = *(state + 7);
    
    for (int i = 0; i < 64; ++i) {
        uint32_t t1 = h + sigma1(e) + choose(e, f, g) + *(k + i) + *(w + i);
        uint32_t t2 = sigma0(a) + majority(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }
    
    *(state + 0) += a;
    *(state + 1) += b;
    *(state + 2) += c;
    *(state + 3) += d;
    *(state + 4) += e;
    *(state + 5) += f;
    *(state + 6) += g;
    *(state + 7) += h;

    delete[] w;
}
