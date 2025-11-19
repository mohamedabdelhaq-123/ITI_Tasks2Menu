#ifndef FUNCSHEADERS_H_INCLUDED
#define FUNCSHEADERS_H_INCLUDED


#ifdef _WIN32
#include <windows.h>
#include <conio.h>  // for getch() on Windows
#else
#include <unistd.h>
#include <ncurses.h>
#endif




#include <vector>
#include <string>

/////////////////////////////////////Prototypes////////////////////////////////////
using namespace std;
void gotoXY(u16 row, u16 col);
void clearScreen();
void resetColor();
void setColor(Color color);

u16 colorChoiceByUser(char*dataFromUser);
void printUserInputColor (u16 userColorChoice, char*dataFromUser);
void printColoredString (char*dataFromUser);
void delaySeconds(u16 seconds);

void initScreen();
void closeScreen();
u32 showMenu(const vector<string>& options);

void newOption();
void displayOption();
void exitOption();
void runMenu (void);
void printMenu(void);

#endif // FUNCSHEADERS_H_INCLUDED
