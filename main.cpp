#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>  // for getch() on Windows
#else
#include <ncurses.h>
#endif


#include "Headers.h"
#include "FuncsHeaders.h"

using namespace std;

int main() {
     // task1
    printColoredString("\n\n\n\n\n\n\n\n============================== Abdelhaq Love Mina ==============================");

    // task2
    printMenu();

    return 0;
}














