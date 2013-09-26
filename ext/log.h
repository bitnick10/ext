#ifndef EXT__LOG_H
#define EXT__LOG_H

#include "ext.h"

#include <iostream>

class Log {
public:
    void Hello() ;
};
void Log::Hello() {
        printf("hello");
    }
#endif