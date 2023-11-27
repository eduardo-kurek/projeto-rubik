#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <algorithm>
#ifdef _WIN32
#include <windows.h>
#endif

#define INFO

class Tunner {

    struct Parameter {
        int min;
        int max;
    };

    struct Result{
        std::vector<int> parameters;
        float value;

        bool operator<(const Result& other) const{
            return this->value < other.value;
        }

        bool operator==(const Result& other) const{
            return this->value == other.value;
        }
    };

    Result NULL_RESULT = {{}, 0.0};

    std::filesystem::path filePath;
    std::vector<Parameter> parameters;
    std::vector<Result> results;
    uint64_t count = 0;
    uint64_t maxCount = 0;
    uint16_t printProgressStep = 20; // 1/20 = 5%

    void increaseCount(){
        this->count++;
        if(this->count % (this->maxCount / this->printProgressStep) == 0){
            float progress = (float)this->count / (float)this->maxCount * 100.0;
            std::cout << "[INFO] " << "[PROGRESSO] " << progress << "%\n";
        }
    }

    std::string mountCmd(std::vector<int> values){
        std::string cmd;
        #ifdef _WIN32 
            cmd = ".\\" + this->filePath.string() + " ";
        #else 
            cmd = "./" + this->filePath.string() + " ";
        #endif
        for(auto& v : values) cmd += std::to_string(v) + " ";
        return cmd;
    }
    
    Result execute(std::vector<int> values){
        std::string cmd = this->mountCmd(values);
        std::ostringstream output;
        this->increaseCount();

        FILE* pipe = popen(cmd.c_str(), "r");
        if(pipe){

            char buffer[128];
            while (fgets(buffer, sizeof(buffer), pipe) != nullptr) output << buffer;
            int status = pclose(pipe);

            // VERIFICANDO O CÓDIGO DE RETORNO DO PROGRAMA
            if(status != 0) return NULL_RESULT;
            return {values, std::stof(output.str())};
        }

        return NULL_RESULT;
    }

    void insertResult(Result result){
        // VERIFICANDO SE O RESULTADO JÁ EXISTE NO VETOR
        if(std::binary_search(this->results.begin(), this->results.end(), result)) return;

        for(uint32_t i = 0; i < this->results.size() - 1; i++){
            if(result.value > this->results[i].value){

                if(result.value > this->results[i+1].value)
                    this->results[i] = this->results[i + 1];
                else{
                    // VALOR É MAIOR QUE I-1 E MENOR QUE I+1, INSERE
                    auto last = this->results[i].value;
                    this->results[i] = result; 
                    #ifdef INFO
                        std::cout << "[INFO] [> " << std::right << std::setw(7) << last << "] Configuração [";
                        for(auto& v : result.parameters) std::cout << v << ", ";
                        std::cout << "\b\b] : " << std::right << std::setw(7) << result.value << " inserida.\n";
                    #endif

                    return;
                }

            }
            // VALOR É MENOR QUE TODOS, NÃO INSERE
            else return; 
        }

        // INSERÇÃO NO FINAL, O VALOR É MAIOR QUE TODOS
        this->results[this->results.size() - 1] = result;
        #ifdef INFO
            std::cout << "[INFO] [  MELHOR ] Configuração [";
            for(auto& v : result.parameters) std::cout << v << ", ";
            std::cout << "\b\b] : " << std::right << std::setw(7) << result.value << " inserida.\n";
        #endif
    }

    void tune(std::vector<int>& values, int index){
        // CASO BASE
        if(index == this->parameters.size()){
            Result result = this->execute(values);
            this->insertResult(result);
            return;
        }

        // CASO RECURSIVO
        for(int i = this->parameters[index].min; i <= this->parameters[index].max; i++){
            values.push_back(i);
            this->tune(values, index + 1);
            values.pop_back();
        }
    }

    void adjustMaxCount(){
        this->maxCount = 1;
        for(auto& p : this->parameters) this->maxCount *= (p.max - p.min + 1);
    }

public:
    Tunner(std::filesystem::path filePath, int resultsSize = 5){
        this->filePath = filePath;
        this->results.resize(resultsSize);
        std::cout << std::fixed << std::setprecision(2);
    }

    void addParameter(Parameter&& param){
        this->parameters.push_back(param);
        this->adjustMaxCount();
    }

    void run(){
        std::vector<int> vec;
        this->tune(vec, 0);
    }

    void writeResults(std::filesystem::path path){
        std::ofstream file(path, std::ios::app);
        file << std::fixed << std::setprecision(2);

        for(auto& r : this->results){
            file << "[RESULTADO] [";
            for(int i = 0; i < r.parameters.size(); i++){
                file << r.parameters[i];
                if(i != r.parameters.size() - 1) file << ", ";
            }
            file << "] : " << std::right << std::setw(7) << r.value << "\n";
        }
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

    Tunner tunner("analysis.out");

    tunner.addParameter({0, 2});
    tunner.addParameter({0, 2});
    tunner.addParameter({0, 2});
    tunner.addParameter({0, 2});
    tunner.addParameter({0, 2});
    tunner.addParameter({0, 2});
    tunner.addParameter({0, 2});
    tunner.addParameter({0, 2});
    tunner.addParameter({0, 2});

    tunner.run();

    tunner.writeResults(output);

    return 0;
}