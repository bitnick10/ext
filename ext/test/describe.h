#ifndef EXT__DESCRIBE_H
#define EXT__DESCRIBE_H

#include "../misc/macros.h"

NS_EXT_BEGIN

template<typename F>
void Describe(std::string description, F f) {
    Spec* spec = Spec::getInstance();
    spec->LevelUp();
    spec->AddApec(description, FunctionType::Describe);
    f();
    spec->LevelDown();
}

template<typename F>
void It(std::string description, F f) {
    Spec* spec = Spec::getInstance();
    spec->LevelUp();
    spec->AddApec(description, FunctionType::It);
    f();
    spec->LevelDown();
}

NS_EXT_END
#endif