#pragma once

#include "auxiliares/Face.h"
#include "auxiliares/constantes.h"
#include "auxiliares/Move.h"
#include <cstdarg>
#include <string>
#include <list>

class Rubik{

private:
    Face faces[6];
    std::list<const Move*> historic;

public:
    Rubik();

    explicit Rubik(const std::string& position);

    void print(bool clear = false) const;

    void reset();

    std::string extract() const;

    void setPosition(const std::string& position);

    void printHistoric();

    void move(int numArgs, ...);

    friend std::ostream &operator<<(std::ostream &os, const Rubik* rubik);

};