#ifndef __SPEC_H__
#define __SPEC_H__

#include <list>
#include <iostream>
#include <string>
#include "../console.h"
enum  class FunctionType {
    Describe,
    It
};
struct SpecInfo {
    int level;
    std::string description;
    FunctionType type;
    std::list<std::string> errors;
};

class Spec {
    std::list<SpecInfo> specList;
    int levelNow;
public:
	int ErrorSum;
	int ExpectSum;
public:
	static Spec& Instance(){
		static Spec instance;
		return instance;
	}
    Spec() {
        this->levelNow = 0;
		this->ErrorSum=0;
		this->ExpectSum=0;
    }
    void LevelUp() {
        this->levelNow++;
    }
    void LevelDown() {
        this->levelNow--;
    }
    int GetLevel() {
        return this->levelNow;
    }
    void Print() {
        for( auto iter = specList.begin(); iter != specList.end(); iter++ ) {
            if((*iter).type == FunctionType::Describe) {
                if (iter != specList.begin() ) {
                    std::cout << std::endl;
                }
                Console::SetConsoleTextColor(Console::Color::CYAN);
            }
            if((*iter).type == FunctionType::It) {
                Console::SetConsoleTextColor(Console::Color::GREEN);
            }
            for(int space = 1; space < (*iter).level; space++) {
                std::cout << "  ";
            }
            std::cout << (*iter).description << std::endl;
            Console::SetConsoleTextColor(Console::Color::RED);
            for( auto i = (*iter).errors.begin(); i != (*iter).errors.end(); i++) {
                for(int space = 1; space < (*iter).level; space++) {
                    std::cout << "  ";
                }
                std::cout << (*i) << std::endl;
            }
            Console::ResetColor();
        }
    }
	void Conclusion(){
		if(this->ErrorSum==0){
			Console::SetConsoleTextColor(Console::Color::GREEN);
			std::cout<<ExpectSum<<" all passed"<<std::endl;
			  Console::ResetColor();
		}else{
			Console::SetConsoleTextColor(Console::Color::RED);
			std::cout<<ErrorSum<<" failed"<<std::endl;
			  Console::ResetColor();
		}

	}
    void AddError(std::string error) {
        specList.back().errors.push_back(error);
    }
    void AddApec(std::string description, FunctionType type ) {
        SpecInfo info;
        info.description = description;
        info.level = levelNow;
        info.type = type;
        specList.push_back(info);
    }
};


#endif