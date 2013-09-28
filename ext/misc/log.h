#ifndef EXT__LOG_H
#define EXT__LOG_H

#include "console.h"

#include <iostream>

class Log {
public:
	void Trace(char* message){
		Console::SetConsoleTextColor(Console::Color::BLUE);
		printf("%s\n",message);
		Console::ResetColor();
	}
};

#endif