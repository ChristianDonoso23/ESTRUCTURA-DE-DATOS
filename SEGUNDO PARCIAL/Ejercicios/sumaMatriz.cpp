#include <iostream>
#include <cstdlib>
#include <ctime>
#define MAX 3

using namespace std;

template<typename T, size_t N>
int sumaRecursivaMatrices(T (&mat1)[N][N], T (&mat2)[N][N], int f, int c, int (*lambda)(int, int)) {
    if (f == 0 && c == 0)
        return lambda(mat1[f][c], mat2[f][c]);
    else {
        if (f > -1) {
            c--;
            if (c >= -1)
                return lambda(mat1[f][c + 1], mat2[f][c + 1]) + sumaRecursivaMatrices(mat1, mat2, f, c, lambda);
            else
                return sumaRecursivaMatrices(mat1, mat2, f - 1, 2, lambda);
        }
    }
    return 0;
}

int main(int argc, char** argv) {
    int mat1[MAX][MAX], mat2[MAX][MAX];
    srand(time(NULL));
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            mat1[i][j] = (int)((rand() % 10));
            mat2[i][j] = (int)((rand() % 10));
        }
    }

    auto sum = [](int a, int b) -> int { return a + b; };

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cout << mat1[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cout << mat2[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "Suma de Matrices es: " << sumaRecursivaMatrices(mat1, mat2, 2, 2, sum) << endl;

    return 0;
}