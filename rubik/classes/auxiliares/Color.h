#pragma once

struct Color{
    char name[10];
    char cod;
    char ch[25];
};

const Color AZUL     = {"Azul", 'B', "\x1b[38;2;1;126;255m"};
const Color AMARELO  = {"Amarelo", 'Y', "\x1b[38;2;245;255;0m"};
const Color VERMELHO = {"Vermelho", 'R', "\x1b[38;2;220;0;0m"};
const Color BRANCO   = {"Branco", 'W', "\033[1;37m"};
const Color LARANJA  = {"Laranja", 'O', "\x1b[38;2;255;138;25m"};
const Color VERDE    = {"Verde", 'G', "\033[38;2;0;225;1m"};