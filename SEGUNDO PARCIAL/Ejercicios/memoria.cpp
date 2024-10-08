#include <iostream>
#include <cstdint>
#include <iomanip>

void printHexVal(uint16_t val){
    std::cout << std::hex << std::setw(2) << std::setfill('0') << val;
}

void printRawMem(uint8_t* p, uint16_t linebytes, uint16_t lines ){
    for (uint16_t l=0; l < lines; ++l){
        std::cout << reinterpret_cast<uint16_t*>(p)<<" ";
        for (uint16_t u=0; u < linebytes; ++u){
            printHexVal(*p);
            ++p;
            std::cout << " ";
        }
        std::cout << "\n";
    }
}

class CGameObject {
public:
    CGameObject(uint16_t x, uint16_t y)
    : m_x(x), m_y(y), m_id(ms_id++) {
        std::cout << "Creating CGameObject " << m_id
        <<"(" << m_x << ", " << m_y<<")"
        <<" at ( " << this << ", " << sizeof(*this)<< ")\n";
    }
    ~CGameObject(){
        std::cout << "Destroying CGameObject " << m_id << "\n";
    }
private:
    static uint32_t ms_id;
    uint32_t m_id;
    uint16_t m_x, m_y;
};

uint32_t CGameObject::ms_id = 1;

int main(){
    CGameObject *g1, *g2;
    uint8_t* p;

    g1 = new CGameObject(1,2);
    g2 = new CGameObject(3,7);

    p = reinterpret_cast<uint8_t*>(g1) - 16;
    printRawMem(p, 16, 4);
    std::cout << "--------------\n";

    delete g2;
    printRawMem(p, 16, 4);
    std::cout << "--------------\n";

    delete g1;
    printRawMem(p, 16, 4);

    return 0;
}