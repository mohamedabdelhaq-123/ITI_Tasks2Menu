#include <iostream>
#include <thread>
#include <chrono>



#include "Headers.h"
#include "FuncsHeaders.h"

using namespace std;
using namespace chrono;
using namespace this_thread;

u16 rowInsertedByUser=InitRowValue, columnInsertedByUser=InitColumnValue;  // here bec ld error mult def in funsheaders.h and in main


void delaySeconds(u16 numberOfSeconds) {
    #ifdef _WIN32
    Sleep(numberOfSeconds * 1000);  // Sleep() expects milliseconds
    #else
    sleep_for(seconds(numberOfSeconds)); // instead of std::this_thread::sleep_for(std::chrono::seconds(seconds)); //sleepfor func takes duration of time object, not just a number
    #endif // _WIN32
}                                                              // so,seconds func convert a normal integer into a time duration object that C++ can understand for timing operations


void gotoXY(u16 row, u16 col) {

    #ifdef _WIN32
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { (SHORT)(col - 1), (SHORT)(row - 1) };
    SetConsoleCursorPosition(h, pos);
    #else
    // ANSI escape code: \033[row;colH
    cout << "\033[" << row << ";" << col << "H";     //Moves the cursor to row and col, \033[ starts the command, H tells the terminal “go here”.
    #endif
}


void clearScreen() {
    #ifdef _WIN32
    system("cls");    // Windows command
    #else
    cout << "\033[2J";              // \033[2J is an ANSI escape code that tells the terminal: “wipe the screen clean”.
    #endif
}


void setColor(Color color) {
#ifdef _WIN32
    int winColor = 0;
    switch(color) {
        case Color::RED:   winColor = 4; break; // Windows red
        case Color::GREEN: winColor = 2; break; // Windows green
        case Color::BLUE:  winColor = 1; break; // Windows blue
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), winColor);
#else                                                                       //\033[ → tells the terminal: “this is a command, not normal text”
    cout << "\033[" << static_cast<int>(color) << "m";                     // <number>m → tells the terminal which color to use
    #endif                                                                  //static_cast<int>(color) Converts the enum into its numeric value so the terminal understands it.
}

void resetColor() {
    #ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // default console color
    #else
    cout << "\033[0m";                            // \033[0m cancels any previous color formatting.
    #endif
}



u16 colorChoiceByUser(char*dataFromUser)
{
    u16 colorChoice=InitColor;
    cout << "Enter row position: ";
    cin >> rowInsertedByUser;
    cout << "Enter column position: ";
    cin >> columnInsertedByUser;
    cout << "\nChoose a color:\n1 - Red\n2 - Green\n3 - Blue\nEnter your choice: ";
    cin >> colorChoice;
    return colorChoice;
}



void printUserInputColor (u16 userColorChoice, char*dataFromUser)
{
        Color chosenColor=InitColor;
        switch(userColorChoice) {
        case 1: chosenColor = RED; break;
        case 2: chosenColor = GREEN; break;
        case 3: chosenColor = BLUE; break;
        default: chosenColor = RED; break; // default to red
        }
        clearScreen();
        gotoXY(rowInsertedByUser, columnInsertedByUser);
        setColor(chosenColor);
        cout << dataFromUser << endl;
}


 void printColoredString (char*dataFromUser)
 {
     printUserInputColor(colorChoiceByUser(dataFromUser),dataFromUser);
     resetColor();
     delaySeconds(InitDelay);
     clearScreen();
 }



 /***********************************Task2************************************/



void initScreen() {  // Prepares terminal for program before the menu is shown
    #ifdef _WIN32
    // nothing to init for basic console
    #else
    initscr();   // sets up the terminal for “curses mode
    cbreak();     // Disables line buffering, so input is sent to your program one character at a time
    noecho();    // prevent typed characters from appearing
    keypad(stdscr, TRUE);  //  Enables special-key input (like arrow keys, function keys....
    start_color();  // Enables color support in ncurses.
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // normal (id,textcolor,backgroundcolor)
    init_pair(2, COLOR_BLUE, COLOR_BLACK);  // chosen one
    #endif // _WIN32
}

void closeScreen() {
    #ifdef _WIN32
    // nothing to init for basic console
    #else
    endwin();  // tells ncurses: “I’m done with your special mode — return control to the normal terminal
    #endif // _WIN32
}


u32 showMenu(const vector<string>& options) {  //displays a menu & lets user navigate it with arrow keys, and returns the selected index item
    u32 n = options.size();
    u32 highlight = 0;
    s32 choice = -1;

    while (true) {
        clearScreen();

        for (u32 i = 0; i < n; i++) {
#ifdef _WIN32
            if (i == highlight) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            } else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            printf("%s\n", options[i].c_str());
#else
            if (i == highlight)
                attron(COLOR_PAIR(2));
            else
                attron(COLOR_PAIR(1));
#endif
        }
#ifdef _WIN32
        int ch = _getch();
        if (ch == 224) { // arrow keys
            ch = _getch();
            switch (ch) {
                case 72: highlight = (highlight - 1 + n) % n; break; // up
                case 80: highlight = (highlight + 1) % n; break;     // down
            }
        } else if (ch == 13) { // Enter
            choice = highlight;
        }
#else
        u32 ch = getch();
        switch (ch) {
            case KEY_UP:
                highlight = (highlight - 1 + n) ; // to be circular if 0 then press up so go to last one
                break;
            case KEY_DOWN:
                highlight = (highlight + 1) ;
                break;
            case '\n':
                choice = highlight;  // currently highlighted item becomes the selected choice.
                break;
        }
#endif
        if (choice != -1)
            break;
    }

    return choice;
}

void waitForBackspace() {
#ifdef _WIN32
    int ch;
    while ((ch = _getch()) != 8); // 8 = BACKSPACE
#else
    u32 ch;
    while ((ch = getch()) != KEY_BACKSPACE);
#endif
}

void newOption() {
#ifdef _WIN32
    system("cls");
    printf("You selected NEW option!\nPress BACKSPACE to return to menu...");
#else
    clear();
    mvprintw(1, 2, "You selected NEW option!");
    mvprintw(3, 2, "Press BACKSPACE to return to menu...");
#endif
    waitForBackspace();
}

void displayOption() {
#ifdef _WIN32
    system("cls");
    printf("You selected DISPLAY option!\nPress BACKSPACE to return to menu...");
#else
    clear();
    mvprintw(1, 2, "You selected DISPLAY option!");
    mvprintw(3, 2, "Press BACKSPACE to return to menu...");
#endif
    waitForBackspace();
}


void exitOption() {
#ifdef _WIN32
    // optional: reset console color before exit
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
    endwin();   // close ncurses
#endif
    exit(0);
}

void runMenu() {
    vector<string> options = { "New", "Display", "Exit" };
    u32 n = options.size();
    u32 highlight = 0;

    while (true) {
        s8 choice = -1;

        // Menu loop
        while (choice == -1) {
#ifdef _WIN32
            system("cls");  // clear console
            for (int i = 0; i < n; i++) {
                if (i == highlight) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                } else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
                printf("%s\n", options[i].c_str());
            }
#else
            clear();
            for (u8 i = 0; i < n; i++)
            {
                if (i == highlight)
                    attron(COLOR_PAIR(2));
                else
                    attron(COLOR_PAIR(1));

                mvprintw(i+5 , 35, options[i].c_str()); //moves the cursor to row (i+5), column 35, and prints the menu option text there.
            }
#endif

#ifdef _WIN32
            int ch = _getch();
            if (ch == 224) {  // arrow keys
                ch = _getch();
                switch (ch) {
                    case 72: highlight = (highlight - 1 + n) % n; break; // up
                    case 80: highlight = (highlight + 1) % n; break;     // down
                }
            } else if (ch == 13) { // Enter
                choice = highlight;
            }
#else
            u32 ch = getch();
            switch (ch) {
                case KEY_UP:
                    highlight = (highlight - 1 + n) % n; // to be circular if 0 then press up so go to last one
                    break;                               // 0-1+3=> 2%3 => 2
                case KEY_DOWN:
                    highlight = (highlight + 1) % n;     // (2+1)%3 => 3%3 => 0
                    break;
                case '\n':
                    choice = highlight;  // currently highlighted item becomes the selected choice.
                    break;  // Enter
            }
#endif
        }

        // Execute selection
        switch (choice) {
            case 0: newOption();
                break;
            case 1: displayOption();
                break;
            case 2: exitOption();
                break;  // program exits
        }
    }
}

    void printMenu(void)
    {
    initScreen();
    runMenu();
    closeScreen();
    }
