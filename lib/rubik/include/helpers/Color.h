#pragma once

#include <string>

struct Color{
    std::string name;
    char cod;
    std::string ch;
    int index;

    static const Color* getColorByCode(char code);
};

const Color BLUE     = {"Azul", 'B', "\x1b[38;2;1;126;255m", 0};
const Color YELLOW   = {"Amarelo", 'Y', "\x1b[38;2;245;255;0m", 1};
const Color RED      = {"Vermelho", 'R', "\x1b[38;2;220;0;0m", 2};
const Color WHITE    = {"Branco", 'W', "\033[1;37m", 3};
const Color ORANGE   = {"Laranja", 'O', "\x1b[38;2;255;138;25m", 4};
const Color GREEN    = {"Verde", 'G', "\033[38;2;0;225;1m", 5};
const Color NONE     = {"None", 'N', " ", -1};

extern const Color* COLORS[6];