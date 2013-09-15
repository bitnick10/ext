#ifndef EXT__LOG_H
#define EXT__LOG_H

#include "console.h"

#include <iostream>

class Log {
public:
    void Hello() ;
};
void Log::Hello() {
        printf("hello");
    }
#endif