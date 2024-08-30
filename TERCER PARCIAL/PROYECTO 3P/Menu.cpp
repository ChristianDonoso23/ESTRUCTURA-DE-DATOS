#include "Menu.h"

int Menu::mostrarMenu(const std::string* options, int n) {
    int selected = 0;
    char ch;

    while (true) {
        system("cls");

        std::cout << "Seleccione una opcion:\n";
        for (int i = 0; i < n; ++i) {
            if (i == selected) {
                std::cout << " -> " << *(options + i) << "\n";
            } else {
                std::cout << "   " << *(options + i) << "\n";
            }
        }

        ch = _getch();
        if (ch == 72) {
            selected = (selected - 1 + n) % n;
        } else if (ch == 80) {
            selected = (selected + 1) % n;
        } else if (ch == 13) {
            return selected;
        }
    }
}
