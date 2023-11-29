#include "rubik/Rubik.h"
#include "rubik/Solver.h"
#include "rubik/auxiliares/1StickerCoord.h"
#include "rubik/auxiliares/Corners.h"
#include "rubik/scores/PontuationTable.h"
#include "rubik/auxiliares/Move.h"
#include "RUBIK/auxiliares/Restriction.h"
#include <iostream>
#include <vector>
#include <fstream>
#ifdef _WIN32
#include <windows.h>
#endif


void print_historic(const Rubik& r, std::ofstream& file){
    std::ostream& output = file.is_open() ? file : std::cout;

    for(auto& h : r.getHistoric()){
        output << h->name << " ";
    }
    output << '\n';
}

int main(int argc, char* argv[]){
    // AJUSTANDO A CODIFICAÇÃO PARA UTF-8
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif

    Rubik r;
    Rubik r2;
    r2.move({R, F, U2, D2, B2, L});

    Solver s(r2, r);
    s.solve(6);

    auto res = s.getFoundedSolves();
    
    std::cout << "Soluções encontradas: ";
    for(auto& x : res){
        for(auto& y : x)
            std::cout << y->name << " ";
        std::cout << "\n";
    }
}