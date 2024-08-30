#include "Grafico.h"
#include <cmath>
using namespace std;

void Grafico::inicializarGraficos() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    setbkcolor(WHITE);
    cleardevice();
}

template <typename T>
void Grafico::graficarConjunto(int x, int y, const char* nombre, T* elementos, int tamano) {
    int cx = getmaxx() / 2 + x;
    int cy = getmaxy() / 2 + y;

    setcolor(BLACK);
    circle(cx, cy, 100);
    setcolor(GREEN);
    outtextxy(cx - 15, cy - 70, const_cast<char*>(nombre));

    setcolor(BLUE);

    double angleStep = 360.0 / tamano;
    double angle = 0;
    int radius = 60;

    for (int i = 0; i < tamano; ++i) {
        stringstream ss;
        ss << *(elementos + i);
        string elemStr = ss.str();

        int posX = cx + static_cast<int>(radius * cos(angle * M_PI / 180.0));
        int posY = cy + static_cast<int>(radius * sin(angle * M_PI / 180.0));

        outtextxy(posX - (elemStr.length() * 5), posY, const_cast<char*>(elemStr.c_str()));

        angle += angleStep;
    }
}




template <typename T>
void Grafico::graficarUnion(T* A, int tamA, T* B, int tamB) {
    setbkcolor(WHITE);
    cleardevice();

    int cx = getmaxx() / 2;
    int cy = getmaxy() / 2;

    setcolor(BLACK);
    circle(cx - 50, cy, 100);
    circle(cx + 50, cy, 100);

    setcolor(RED);
    outtextxy(cx - 90, cy - 70, const_cast<char*>("A"));
    outtextxy(cx + 70, cy - 70, const_cast<char*>("B"));

    setcolor(BLUE);
    outtextxy(cx - 30, cy - 150, const_cast<char*>("Union AB"));

    T* ptrA = A;
    T* ptrB = B;
    int xA = cx - 100, yA = cy;
    int xB = cx + 100, yB = cy;
    int xAB = cx - 20, yAB = cy;

    for (int i = 0; i < tamA; ++i) {
        bool encontrado = false;
        for (int j = 0; j < tamB; ++j) {
            if (*(ptrA + i) == *(ptrB + j)) {
                encontrado = true;
                break;
            }
        }
        stringstream ss;
        ss << *(ptrA + i);
        string elemStr = ss.str();
        if (encontrado) {
            outtextxy(xAB, yAB, const_cast<char*>(elemStr.c_str()));
            yAB += 20;
        } else {
            outtextxy(xA, yA, const_cast<char*>(elemStr.c_str()));
            yA += 20;
        }
    }

    for (int i = 0; i < tamB; ++i) {
        bool encontrado = false;
        for (int j = 0; j < tamA; ++j) {
            if (*(ptrB + i) == *(ptrA + j)) {
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            stringstream ss;
            ss << *(ptrB + i);
            string elemStr = ss.str();
            outtextxy(xB, yB, const_cast<char*>(elemStr.c_str()));
            yB += 20;
        }
    }
}


template <typename T>
void Grafico::graficarInterseccion(T* A, int tamA, T* B, int tamB) {
    setbkcolor(WHITE);
    cleardevice();
    
    int cx = getmaxx() / 2;
    int cy = getmaxy() / 2;

    setcolor(BLACK);
    circle(cx - 50, cy, 100);
    circle(cx + 50, cy, 100);

    setcolor(GREEN);
    outtextxy(cx - 90, cy - 70, const_cast<char*>("A"));
    outtextxy(cx + 70, cy - 70, const_cast<char*>("B"));

    setcolor(BLUE);
    outtextxy(cx - 35, cy - 150, const_cast<char*>("Interseccion AB"));

    T* ptrA = A;
    T* ptrB = B;
    int xA = cx - 100, yA = cy;
    int xB = cx + 100, yB = cy;
    int xAB = cx - 20, yAB = cy;

    bool interseccionEncontrada = false;
    for (int i = 0; i < tamA; ++i) {
        for (int j = 0; j < tamB; ++j) {
            if (*(ptrA + i) == *(ptrB + j)) {
                interseccionEncontrada = true;
                break;
            }
        }
        if (interseccionEncontrada) {
            break;
        }
    }

    if (interseccionEncontrada) {
        setfillstyle(SOLID_FILL, LIGHTCYAN);
        floodfill(cx, cy, BLACK);
        yAB = cy;
        for (int i = 0; i < tamA; ++i) {
            for (int j = 0; j < tamB; ++j) {
                if (*(ptrA + i) == *(ptrB + j)) {
                    setbkcolor(LIGHTCYAN);
                    setcolor(BLACK);
                    stringstream ss;
                    ss << *(ptrA + i);
                    string elemStr = ss.str();
                    outtextxy(xAB, yAB, const_cast<char*>(elemStr.c_str()));
                    yAB += 20;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < tamA; ++i) {
        bool enInterseccion = false;
        for (int j = 0; j < tamB; ++j) {
            if (*(ptrA + i) == *(ptrB + j)) {
                enInterseccion = true;
                break;
            }
        }
        if (!enInterseccion) {
            setbkcolor(WHITE);
            setcolor(BLACK);
            stringstream ss;
            ss << *(ptrA + i);
            string elemStr = ss.str();
            outtextxy(xA, yA, const_cast<char*>(elemStr.c_str()));
            yA += 20;
        }
    }

    for (int i = 0; i < tamB; ++i) {
        bool enInterseccion = false;
        for (int j = 0; j < tamA; ++j) {
            if (*(ptrB + i) == *(ptrA + j)) {
                enInterseccion = true;
                break;
            }
        }
        if (!enInterseccion) {
            setbkcolor(WHITE);
            setcolor(BLACK);
            stringstream ss;
            ss << *(ptrB + i);
            string elemStr = ss.str();
            outtextxy(xB, yB, const_cast<char*>(elemStr.c_str()));
            yB += 20;
        }
    }

    setcolor(GREEN);
    outtextxy(cx - 90, cy - 70, const_cast<char*>("A"));
    outtextxy(cx + 70, cy - 70, const_cast<char*>("B"));

    setcolor(BLUE);
    outtextxy(cx - 35, cy - 150, const_cast<char*>("Interseccion AB"));
}


template <typename T>
void Grafico::graficarDiferencia(T* A, int tamA, T* B, int tamB, bool ab) {
    setbkcolor(WHITE);
    cleardevice();
    int tamDiferencia;
    T* diferenciaAB;

    if (ab) {
        diferenciaAB = Conjunto<T>::diferenciaAmenosB(A, tamA, B, tamB, tamDiferencia);
        graficarConjunto(0, 0, "A - B", diferenciaAB, tamDiferencia);
        setcolor(BLUE);
        outtextxy(getmaxx() / 2 - 55, getmaxy() / 2 - 200, const_cast<char*>("Diferencia A - B"));
    } else {
        diferenciaAB = Conjunto<T>::diferenciaBmenosA(B, tamB, A, tamA, tamDiferencia);
        graficarConjunto(0, 0, "B - A", diferenciaAB, tamDiferencia);
        setcolor(BLUE);
        outtextxy(getmaxx() / 2 - 55, getmaxy() / 2 - 200, const_cast<char*>("Diferencia B - A"));
    }

    delete[] diferenciaAB;
}


template <typename T>
void Grafico::graficarComplemento(T* universo, int tamU, T* A, int tamA, bool a) {
    setbkcolor(WHITE);
    cleardevice();
    int tamComplemento;
    T* complementoA;

    if (a) {
        complementoA = Conjunto<T>::complementoConjunto(universo, tamU, A, tamA, tamComplemento);
        graficarConjunto(0, 0, "  A' ", complementoA, tamComplemento);
        setcolor(MAGENTA);
        outtextxy(getmaxx() / 2 - 55, getmaxy() / 2 - 150, const_cast<char*>("Complemento de A"));
    } else {
        complementoA = Conjunto<T>::complementoConjunto(universo, tamU, A, tamA, tamComplemento);
        graficarConjunto(0, 0, " B' ", complementoA, tamComplemento);
        setcolor(MAGENTA);
        outtextxy(getmaxx() / 2 - 55, getmaxy() / 2 - 150, const_cast<char*>("Complemento de B"));
    }

    delete[] complementoA;
}

template <typename T>
void Grafico::graficarConjuntosSeparados(T* A, int tamA, T* B, int tamB) {
    setbkcolor(WHITE);
    cleardevice();
    int cx = getmaxx() / 2;
    int cy = getmaxy() / 2;
    graficarConjunto(-150, 0, "", A, tamA);
    graficarConjunto(150, 0, "", B, tamB);
    setcolor(BLACK);
    outtextxy(cx - 180, cy - 120, const_cast<char*>("Conjunto A"));
    outtextxy(cx + 110, cy - 120, const_cast<char*>("Conjunto B"));
}
