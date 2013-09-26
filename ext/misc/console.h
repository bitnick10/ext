#ifndef EXT__CONSOLE_H
#define EXT__CONSOLE_H

#include <Windows.h>
#include <iostream>

class Console {
    //BLACK   = "\x1b[30;3m"
    //RED     = "\x1b[31;3m"
    //GREEN   = "\x1b[32;3m"
    //YELLOW  = "\x1b[33;3m"
    //BLUE    = "\x1b[34;3m"
    //MAGENTA = "\x1b[35;3m"
    //CYAN    = "\x1b[36;3m"
    //WHITE   = "\x1b[37;3m"
public:
    enum class Color {
        //BLACK   = 0,
        RED = FOREGROUND_RED , 
        GREEN = FOREGROUND_GREEN ,
        YELLOW = FOREGROUND_GREEN | FOREGROUND_RED ,
        BLUE = FOREGROUND_BLUE ,
        MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE ,
        CYAN = FOREGROUND_BLUE | FOREGROUND_GREEN ,
        WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
    };
    static bool is_intensity;
    static void PrintAllColors() {
        SetConsoleTextColor(Color::RED);
        printf("RED hello\n");
        SetConsoleTextColor(Color::GREEN);
        printf("GREEN hello\n");
        SetConsoleTextColor(Color::YELLOW);
        printf("YELLOW hello\n");
        SetConsoleTextColor(Color::BLUE);
        printf("BLUE hello\n");
        SetConsoleTextColor(Color::MAGENTA);
        printf("MAGENTA hello\n");
        SetConsoleTextColor(Color::CYAN);
        printf("CYAN hello\n");
        SetConsoleTextColor(Color::WHITE);
        printf("WHITE hello\n");
    }
	static void ResetColor(){
		SetConsoleTextColor(Color::WHITE);
	}
    static void SetConsoleTextColor(Color color) {
        int foreground = (int)color;
        if(is_intensity) {
            foreground |= FOREGROUND_INTENSITY;
        }
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdout, foreground);
    }
};
bool Console::is_intensity = false;
#endif