#pragma once

#include "auxiliares/Face.h"
#include "auxiliares/constantes.h"
#include <string>

class Rubik{

private:
    Face* faces[6];

public:
    Rubik();

    explicit Rubik(const std::string& position);

    void print(bool clear = false) const;

    void reset();

    std::string extract() const;

    void setPosition(const std::string& position);

    ~Rubik();

    friend std::ostream &operator<<(std::ostream &os, const Rubik* rubik);

};