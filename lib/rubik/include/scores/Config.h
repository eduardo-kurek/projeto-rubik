#pragma once

#include <iostream>

class Config{

public:
    virtual std::string toString() = 0;
    void print(){
        std::cout << this->toString();
    }
    
};