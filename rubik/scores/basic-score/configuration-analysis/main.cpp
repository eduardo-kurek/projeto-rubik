#include <iostream>
#include <fstream>
#include <filesystem>
#include <utility>
#include <cmath>
#include <omp.h>
#include "../BasicScore.h"
#include "../../PontuationTable.h"
#ifdef _WIN32
#include <windows.h>
#endif

#define DEBUG

using namespace std;

class Analyzer{

    private:

    filesystem::path scramblePath = "../../../../scrambles/";
    vector<string> fileNames;
    vector<string> config;
    vector<float> expectedPontuations = {95,90,85,80,75,70,65,60,55,50,45,40,35,30,25,20,15,10,5,0};
    PontuationTable* table = nullptr;
    vector<float> result;

    public:

    Analyzer(filesystem::path scramblePath, vector<string> fileNames, vector<string> config){
        this->scramblePath = scramblePath;
        this->fileNames = fileNames;
        this->config = config;
    }

    bool validate_files(){
        for (const auto& fileName : this->fileNames) {
            filesystem::path filePath = this->scramblePath / fileName;
            if (!filesystem::exists(filePath)){
                cerr << fileName << " não existe dentro do caminho fornecido.\n";
                return false;
            }
        }
        return true;
    }

    bool mount_table(){
        // MONTANDO TABELA DE PONTUAÇÃO ATRAVÉS DOS VALORES INFORMADOS
        std::vector<float> cornerPontuation;
        std::vector<float> edgePontuations;

        for(int i = 1; i < 10; i++){
            if(i < 6) cornerPontuation.push_back(stof(this->config[i]));
            else edgePontuations.push_back(stof(this->config[i]));
        }

        // VERIFICANDO SE O PRIMEIRO VALOR DE CADA VETOR É O MAIOR DO VETOR INTEIRO
        if(*std::max_element(cornerPontuation.begin(), cornerPontuation.end()) != cornerPontuation[0])
            return false;
        if(*std::max_element(edgePontuations.begin(), edgePontuations.end()) != edgePontuations[0])
            return false;

        this->table = new PontuationTable(cornerPontuation, edgePontuations);
        return true;
    }

    void print_pontuations(){
        if(this->result.size() != 20) return;

        cout << "{\n";

        for(int i = 0; i < this->result.size(); i++){
            cout << "\t\"" << i+1 << "\": ";
            cout << fixed << setprecision(2) << this->result[i];
            cout << ",\n";
        }

        cout << "\b}\n";
    }

    float analyse(){
        if(this->table == nullptr) 
            throw runtime_error("É preciso validar a tabela de pontuação antes de analisar.");

        
    }

};

int main(int argc, char* argv[]){
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif

    // VALIDANDO PARAMETROS
    if(argc < 10){
        std::cerr << "É preciso informar os 9 valores da tabela de pontuação, primeiro as corners, depois as edges.\n";
        return 1;
    }

    filesystem::path path = "../../../../scrambles/";
    vector<string> fileNames = {
        "1move.scr", "2moves.scr", "3moves.scr", "4moves.scr", "5moves.scr",
        "6moves.scr", "7moves.scr", "8moves.scr", "9moves.scr", "10moves.scr",
        "11moves.scr", "12moves.scr", "13moves.scr", "14moves.scr", "15moves.scr",
        "16moves.scr", "17moves.scr", "18moves.scr", "19moves.scr", "20moves.scr"
    };

    vector<string> args;
    for(int i = 1; i < argc; i++)
        args.push_back(argv[i]);
    

    Analyzer* analyzer = new Analyzer(path, fileNames, args);

    if(!analyzer->validate_files()) return 2;
    if(!analyzer->mount_table()) return 3;


    #ifdef DEBUG
    analyzer->print_pontuations();
    #endif

    analyzer->analyse();

    return 0;
}