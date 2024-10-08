#pragma once

#include <iostream>
#include <iomanip>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include "scores/basic-score/BasicScore.h"
#include "scores/Analyzer.h"

template <typename TAnalyzer, typename TScore, typename TConfig>
requires std::derived_from<TAnalyzer, Analyzer<TScore, TConfig>>
class Tunner {

protected:

    struct Parameter{
        float min;
        float max;
        float minExclude;
        float maxExclude;

        Parameter(float min, float max, float minExclude = 0, float maxExclude = 0){
            this->min = min;
            this->max = max;
            this->minExclude = minExclude;
            this->maxExclude = maxExclude;
        }
    };

    struct Result{
        std::vector<float> parameters;
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
        std::vector<float> values;
        std::vector<Parameter> params;
    };

    Result NULL_RESULT = {{}, 0.0};

    TAnalyzer* analyzer = nullptr;
    std::vector<Parameter> parameters;
    std::vector<Result> results;
    uint64_t count = 0;
    uint64_t maxCount = 0;
    uint16_t printProgressStep = 20; // 1/20 = 5%
    std::chrono::seconds elapsed;
    int s;

    TConfig virtual getConfig(std::vector<float>& values) = 0;

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

            float res = this->analyzer->analyze(getConfig(set.values));
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
    Tunner(TAnalyzer& analyzer, int resultsSize = 5){
        this->analyzer = &analyzer;
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
        set.values = std::vector<float>();
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