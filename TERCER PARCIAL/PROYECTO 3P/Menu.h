#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <conio.h>
#include <string>

class Menu {
public:
    static int mostrarMenu(const std::string* options, int n);
};

#include "Menu.cpp"

#endif
