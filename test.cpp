#include "rubik/Rubik.h"
#include "rubik/Solver.h"
#include "rubik/auxiliares/StickerCoord.h"
#include "rubik/auxiliares/Corners.h"
#include "rubik/scores/PontuationTable.h"
#include "rubik/auxiliares/Move.h"
#include "RUBIK/auxiliares/Restriction.h"
#include "managers/DatabaseManager.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char* argv[]){
    // AJUSTANDO A CODIFICAÇÃO PARA UTF-8
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif

    DatabaseManager* database = new DatabaseManager();

    database->createTable("teste", {"id", "nome"}, {"INTEGER", "TEXT"});
    database->insert_one("teste", {"id", "nome"}, {"1", "teste"}, true);
    std::vector<std::vector<std::string>> results = database->select("teste", {"id", "nome"}, true);

    for (const auto& result : results) {
        for(const auto& column : result)
            std::cout << column << " ";
        std::cout << std::endl;
    }

    database->dropTable("teste");

}