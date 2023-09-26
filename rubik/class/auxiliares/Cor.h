#pragma once

struct Cor{
    char nome[10];
    char cod;
    char ch[25];
};

const Cor AZUL     = {"Azul", 'B', "\x1b[38;2;1;126;255m"};
const Cor AMARELO  = {"Amarelo", 'Y', "\x1b[38;2;245;255;0m"};
const Cor VERMELHO = {"Vermelho", 'R', "\x1b[38;2;220;0;0m"};
const Cor BRANCO   = {"Branco", 'W', "\033[1;37m"};
const Cor LARANJA  = {"Laranja", 'O', "\x1b[38;2;255;138;25m"};
const Cor VERDE    = {"Verde", 'G', "\033[38;2;0;225;1m"};