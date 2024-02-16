#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
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

class Tunner {

    struct Parameter{
        int min;
        int max;
        std::unordered_set<int> excludes;

        Parameter(int min, int max, std::unordered_set<int> excludes = {}){
            this->min = min;
            this->max = max;
            this->excludes = excludes;
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

    std::filesystem::path filePath;
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

            for(int i = set.values.size()-1; i >= 0 ; i--)
                if(set.values[i] < set.params[i].min || set.values[i] > set.params[i].max)
                    return;

            Result result = this->execute(set.values);
            if(!(result == NULL_RESULT)) this->insertResult(result);
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

    std::vector<AnalysisSet> prepare_analysis_set(){
        // Obtendo o Parametro com mair range
        int maxRange = 0;
        int maxI = 0;
        for(int i = 0; i < this->parameters.size(); i++){
            auto& p = this->parameters[i];
            int range = p.max - p.min + 1;
            if(range > maxRange){
                maxRange = range;
                maxI = i;
            }
        }

        // Preparando os parametros para a execução
        std::vector<AnalysisSet> analysisSets;
        for(int i = 0; i < maxRange; i++){
            AnalysisSet set;

            // Adiciona cada paramentro existente na classe ao set
            for(auto& param : this->parameters){
                int min = param.min, max = param.min + i, k = max;

                // Se max for maior param.max, significa que o range do parametro foi extrapolado
                if(max > param.max){
                    max = param.max; // Portanto, max será o valor máximo do parametro
                    k++; // E k incrementa, para agora incluir o ultimo parametro no loop a seguir
                }

                std::unordered_set<int> excludes;
                for(int j = min; j < k; j++) excludes.insert(j);
                
                set.params.push_back({min, max, excludes});
            }

            analysisSets.push_back(set);
        }

        return analysisSets;
    }

public:
    Tunner(std::filesystem::path filePath, int resultsSize = 5){
        this->filePath = filePath;
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