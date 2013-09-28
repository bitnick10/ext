#ifndef EXT__LOG_H
#define EXT__LOG_H

#include "console.h"

#include <iostream>
NS_EXT_BEGIN
class Log {
public:
    Log& operator<<(Log & (*func)(Log&)) {
        func(*this);
        return *this;
    }
    template <typename T>
    Log& operator<<(T message) {
        console << message;
        return *this;
    }
};

Log log;

inline Log& trace(Log& log) {
    console << blue;
    return log;
}
NS_EXT_END
#endif