#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include "../BasicScore.h"
#include "../../PontuationTable.h"
#include <type_traits>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>
#include <omp.h>
#include <chrono>
#include <unordered_set>
#ifdef _WIN32
#include <windows.h>
#endif

#define INFO

using string = std::string;

template<typename T>
using vector = std::vector<T>;

template <typename TScore, typename = std::enable_if_t<std::is_base_of<Score, TScore>::value>>
class AnalyzerMultiple{

    private:
    
    PontuationTable* table = nullptr;
    TScore* score = nullptr;
    vector<vector<string>> fileContents;

    vector<float> expectedPontuations = {95,90,85,80,75,70,65,60,55,50,45,40,35,30,25,20,15,10,5,0};
    vector<float> pontuations;


    float calculate_file(int i){
        float sum = 0;
        int count = 0;

        for(int j = 0; j < this->fileContents[i].size(); j++){
            string line = this->fileContents[i][j];
            std::vector<const Move*> moves = Move::stringToMoves(line);
            Rubik rubik;
            rubik.move(moves);

            sum += this->score->calculateNormalized(rubik);
            count++;
        }

        return sum / count;
    }

    void calculate_pontuations(){
        this->pontuations = vector<float>();
        this->pontuations.resize(20);

        #pragma omp parallel for
        for(int i = 0; i < 20; i++)
            this->pontuations[i] = this->calculate_file(i);
    }

    bool mount_table(vector<int> config){
        // MONTANDO TABELA DE PONTUAÇÃO ATRAVÉS DOS VALORES INFORMADOS
        vector<float> cornerPontuation;
        vector<float> edgePontuations;

        for(int i = 0; i < 8; i++){
            if(i < 4) cornerPontuation.push_back(config[i]);
            else edgePontuations.push_back(config[i]);
        }

        // VERIFICANDO SE O PRIMEIRO VALOR DE CADA VETOR É O MAIOR DO VETOR INTEIRO
        if(*std::max_element(cornerPontuation.begin(), cornerPontuation.end()) != cornerPontuation[0])
            return false;
        if(*std::max_element(edgePontuations.begin(), edgePontuations.end()) != edgePontuations[0])
            return false;

        this->table = new PontuationTable(cornerPontuation, edgePontuations, config[8]);
        this->score = new TScore(this->table);
        return true;
    }

    public:

    AnalyzerMultiple() = default;

    AnalyzerMultiple(string& scramble_path){
        for(int i = 0; i < 20; i++){
            std::ifstream file(scramble_path + "scramble_" + std::to_string(i+1) + ".scr");
            if(!file.is_open()){
                std::cerr << "[ERRO] [ARQUIVO] O arquivo " << scramble_path + "scramble_" + std::to_string(i+1) + ".scr" << " não pôde ser aberto.\n";
                throw std::runtime_error("Arquivo não encontrado.");
            }

            vector<string> lines;
            string line;
            while(std::getline(file, line)) lines.push_back(line);
            this->fileContents.push_back(lines);
        }
    }

    float analyse(vector<int> config){
        if(config.size() != 9) return 0;
        if(!this->mount_table(config)) return 0;
        this->calculate_pontuations();

        float sum = 0;

        // CALCULANDO O ERRO MÉDIO QUADRÁTICO (MSE)
        #pragma omp parallel for reduction(+:sum)
        for(int i = 0; i < this->pontuations.size(); i ++){
            float diff = abs(this->pontuations[i] - this->expectedPontuations[i]);
            sum += diff * diff;
        }

        return sum;
    }

    float getResult(){ return this->result; }

};

class Tunner {

    struct Parameter{
        int min;
        int max;
        int minExclude;
        int maxExclude;

        Parameter(int min, int max, int minExclude = 0, int maxExclude = 0){
            this->min = min;
            this->max = max;
            this->minExclude = minExclude;
            this->maxExclude = maxExclude;
        }
    };

    struct Result{
        std::vector<int> parameters;
        float value;

        bool operator<(const Result& other) const{
            return this->value < other.value;
        }

        bool operator>(const Result& other) const{
            return this->value > other.value;
        }

        bool operator==(const Result& other) const{
            return this->value == other.value;
        }
    };

    struct AnalysisSet{
        std::vector<int> values;
        std::vector<Parameter> params;
    };

    Result NULL_RESULT = {{}, 0.0};

    AnalyzerMultiple<BasicScore> analyzer;
    std::vector<Parameter> parameters;
    std::vector<Result> results;
    uint64_t count = 0;
    uint64_t maxCount = 0;
    uint16_t printProgressStep = 20; // 1/20 = 5%
    std::chrono::seconds elapsed;
    int s;

    void increaseCount(){
        this->count++;
        if(this->count % (this->maxCount / this->printProgressStep) == 0){
            float progress = (float)this->count / (float)this->maxCount * 100.0;
            std::cout << "[INFO] " << "[PROGRESSO] " << progress << "%\n";
        }
    }

    void insertResult(Result result){
        // VERIFICANDO SE O RESULTADO JÁ EXISTE NO VETOR
        if(std::binary_search(this->results.begin(), this->results.end(), result, std::greater<Result>()))
            return;

        for(uint32_t i = 0; i < this->results.size() - 1; i++){
            if(result.value < this->results[i].value){

                if(result.value < this->results[i+1].value)
                    this->results[i] = this->results[i + 1];
                else{
                    // VALOR É MENOR QUE I-1 E MAIOR QUE I+1, INSERE
                    auto last = this->results[i].value;
                    this->results[i] = result; 

                    #ifdef INFO
                        std::cout << "[INFO] [< " << std::right ;
                        if(last == std::numeric_limits<float>::max()) std::cout << std::setw(10) << "∞";
                        else std::cout << std::setw(8) << last;
                        std::cout << "] Configuração [";
                        for(auto& v : result.parameters) std::cout << v << ", ";
                        std::cout << "\b\b] : " << std::right << std::setw(7) << result.value << " inserida.\n";
                    #endif

                    return;
                }

            }
            // VALOR É MAIOR QUE TODOS, NÃO INSERE
            else return; 
        }

        // INSERÇÃO NO FINAL, O VALOR É MENOR QUE TODOS
        this->results[this->results.size() - 1] = result;
        #ifdef INFO
            std::cout << "[INFO] [  MELHOR  ] Configuração [";
            for(auto& v : result.parameters) std::cout << v << ", ";
            std::cout << "\b\b] : " << std::right << std::setw(7) << result.value << " inserida.\n";
        #endif
    }

    void tune(AnalysisSet set, int index){
        // CASO BASE
        if(index == set.params.size()){
            this->increaseCount();

            bool flag = false;
            for(int i = set.values.size()-1; i >= 0 ; i--){
                if(set.params[i].minExclude == set.params[i].maxExclude){
                    flag = true;
                    break;
                }
                if(set.values[i] < set.params[i].minExclude || set.values[i] > set.params[i].maxExclude){
                    flag = true;
                    break;
                }
            }
            if(!flag) return;

            float res = this->analyzer.analyse(set.values);
            if(res) this->insertResult({set.values, res});
            return;
        }

        // CASO RECURSIVO
        for(int i = this->parameters[index].min; i <= this->parameters[index].max; i++){
            set.values.push_back(i);
            this->tune(set, index + 1);
            set.values.pop_back();
        }
    }

    void adjustMaxCount(){
        this->maxCount = 1;
        for(auto& p : this->parameters) this->maxCount *= (p.max - p.min + 1);
    }

public:
    Tunner() = default;

    Tunner(AnalyzerMultiple<BasicScore> analyzer, int resultsSize = 5){
        this->analyzer = analyzer;
        this->results.resize(resultsSize);
        Result maxResult = {{}, std::numeric_limits<float>::max()};
        for(auto& r : this->results) r = maxResult;

        std::cout << std::fixed << std::setprecision(2);
    }

    void addParameter(Parameter&& param){
        this->parameters.push_back(param);
        this->adjustMaxCount();
    }

    void run(){
        std::chrono::_V2::high_resolution_clock::time_point start;
        start = std::chrono::high_resolution_clock::now();

        AnalysisSet set;
        set.params = this->parameters;
        set.values = std::vector<int>();
        this->tune(set, 0);

        std::chrono::_V2::high_resolution_clock::time_point end;
        end =std::chrono::high_resolution_clock::now();
        this->elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    }

    void writeResults(std::filesystem::path path){
        std::ofstream file(path, std::ios::app);
        file << std::fixed << std::setprecision(2);

        file << "COMBINAÇÕES: ";
        for(auto& p : this->parameters)
            file << "[" << p.min << ", " << p.max << "] ";
        file << std::endl;

        file << "QUANTIDADES TESTADAS: " << this->count << std::endl;
        for(auto& r : this->results){
            file << "[RESULTADO] [";
            for(int i = 0; i < r.parameters.size(); i++){
                file << r.parameters[i];
                if(i != r.parameters.size() - 1) file << ", ";
            }
            file << "] : " << std::right << std::setw(7) << r.value << "\n";
        }
        file << "TEMPO DECORRIDO: " << this->elapsed.count() << "s" << std::endl;

        file << std::endl;
    }

    std::vector<Result> getResults(){ return this->results; }
    uint64_t getCount(){ return this->count; }
    uint64_t getMaxCount(){ return this->maxCount; }

};
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
int main(int argc, char* argv[]){
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif

    if(argc < 2){
        std::cout << "[ERRO] [ARGUMENTOS] Nenhum arquivo de saída foi especificado.\n";
        return 1;
    }

    std::filesystem::path output = argv[1];

    std::string separator = "/";
    #ifdef _WIN32
        separator = "\\";
    #endif

    string scramblePath = ".."+separator+".."+separator+".."+separator+".."+separator;
    scramblePath += "database"+separator+"scrambles"+separator;

    AnalyzerMultiple<BasicScore> analyzer(scramblePath);
    Tunner tunner(analyzer);

    tunner.addParameter({0, 1});
    tunner.addParameter({0, 1});
    tunner.addParameter({0, 1});
    tunner.addParameter({0, 1});
    tunner.addParameter({0, 1});
    tunner.addParameter({0, 1});
    tunner.addParameter({0, 1});
    tunner.addParameter({0, 1});
    tunner.addParameter({1, 20});

    tunner.run();

    tunner.writeResults(output);

    return 0;
}