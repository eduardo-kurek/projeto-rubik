#include "../rubik/Rubik.h"
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

void __populate_all_possibilities(Rubik last, int depth, std::string fileName, int& count, int max){
    for(auto& move : last.getValidMoves()){

        // VERIFICANDO SE AINDA É NECESSÁRIO IMPRIMIR MAIS MOVIMENTOS
        if(count == max) return;

        if(depth == 0){
            // MOVIMENTANDO MODELO ATUAL
            count++;
            Rubik model = last;
            model.move(1, move);

            // IMPRESSÃO DO HISTÓRICO
            std::ofstream file(fileName, std::ios_base::app);
            print_historic(model, file);
            file.close();
        }
        else{
            // INDO MAIS UM MOVIMENTO A FUNDO
            Rubik model = last;
            model.move(1, move);
            __populate_all_possibilities(model, depth-1, fileName, count, max);
        }

    }
}

void populate_all_possibilities(int moves_quantity, int max, std::string fileName){
    // LIMPANDO O ARQUIVO DE TEXTO
    std::ofstream file(fileName);
    file.clear();

    // POPULANDO O ARQUIVO DE TEXTO
    int count = 0;
    Rubik r;
    __populate_all_possibilities(r, moves_quantity-1, fileName, count, max);
}

void populate_scrambled(int moves_quantity, int max, std::string fileName){
    std::ofstream file(fileName);
    for(int i = 0; i < max; i++){
        Rubik r;
        r.scramble(moves_quantity);
        print_historic(r, file);
    }
    file.close();
}

int main(int argc, char* argv[]){
    // AJUSTANDO A CODIFICAÇÃO PARA UTF-8
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif


    if(argc < 3){
        std::cout << "É preciso informar dois argumentos para este programa: A seed, e a quantidade de embaralhamentos em cada arquivo\n";
        return 1;
    }
    int seed = atoi(argv[1]);
    int max = atoi(argv[2]);

    // POPULANDO 1 E 2 MOVIMENTOS
    populate_all_possibilities(1, max, "scrambles/1move.txt");
    populate_all_possibilities(2, max, "scrambles/2moves.txt");
    populate_all_possibilities(3, max, "scrambles/3moves.txt");

    // POPULANDO RESTANTES
    for(int i = 4; i <= 20; i++){
        std::string fname = "scrambles/" + std::to_string(i) + "moves.txt";
        populate_scrambled(i, max, fname);
    }
    
}