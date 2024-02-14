#include "DatabaseManager.h"
#include <iostream>
#include <fstream>
#include <ctime>

void Log::clear(){
    string path = this->relativePath + "db.log";
    std::ofstream file(path, std::ios::out | std::ios::trunc);
    if (!file.is_open()) return;
    file.close();
}

Log::Log(string relativePath){ this->relativePath = relativePath; }

void Log::info(std::string message)
{
    string path = this->relativePath + "db.log";
    std::ofstream file(path, std::ios::out | std::ios::app);
    if (!file.is_open()) return;

    time_t currentTime = time(nullptr);
    tm* localTime = localtime(&currentTime);

    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localTime);

    file << "[" << timestamp << "] [INFO] " << message << std::endl;
    file.close();
}

void Log::error(string message){
    string path = this->relativePath + "db.log";
    std::ofstream file(path, std::ios::out | std::ios::app);
    if (!file.is_open()) return;

    time_t currentTime = time(nullptr);
    tm* localTime = localtime(&currentTime);

    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localTime);

    file << "[" << timestamp << "] [ERROR] " << message << std::endl;
    file.close();
}

inline string DatabaseManager::encapsulateVector(vector<string> columns){
    string result = "(";
    for(int i = 0; i < columns.size(); i++){
        result += columns[i];
        if(i < columns.size() - 1) result += ", ";
    }
    result += ")";
    return result;
}

inline void DatabaseManager::endSql(string& sql){
    sql += ";";
}

void DatabaseManager::dropTable(const string &tableName){
    string sql = "DROP TABLE IF EXISTS " + tableName;
    this->endSql(sql);

    bool log = true;
    if(this->log == nullptr) log = false;
    
    if(log) this->log->info(sql);

    char* err;
    if(sqlite3_exec(this->db, sql.c_str(), NULL, 0, &err) != SQLITE_OK){
        if(log) this->log->error(err);
        std::cerr << "Erro ao deletar tabela: " << err << std::endl;
    }
}

DatabaseManager::~DatabaseManager(){
    sqlite3_close(this->db);
    if(this->log != nullptr) delete this->log;
}

DatabaseManager::DatabaseManager(string dbPath){
    this->dbPath = dbPath + "rubik.db";
    sqlite3_open(this->dbPath.c_str(), &this->db);
}

DatabaseManager::DatabaseManager(Log* log, string dbPath){
    this->dbPath = dbPath + "rubik.db";
    this->log = log;
    this->log->clear();
    sqlite3_open(this->dbPath.c_str(), &this->db);
}

void DatabaseManager::createTable(const string& tableName, vector<string> columns, vector<string> types){
    if(columns.size() != types.size())
        throw "Erro: quantidade de colunas e tipos diferentes";

    vector<string> columnsTypes;
    for(int i = 0; i < columns.size(); i++)
        columnsTypes.push_back(columns[i] + " " + types[i]);

    string sql = "CREATE TABLE IF NOT EXISTS " + tableName + encapsulateVector(columnsTypes);
    this->endSql(sql);

    bool log = true;
    if(this->log == nullptr) log = false;

    if(log) this->log->info(sql);

    char* err;
    if(sqlite3_exec(this->db, sql.c_str(), NULL, 0, &err) != SQLITE_OK){
        if(log) this->log->error(err);
        std::cerr << "Erro ao criar tabela: " << err << std::endl;
    }
}

void DatabaseManager::insert(const string& tableName, vector<string> columns, vector<string> values, bool log){
    if(columns.size() != values.size())
        throw "Erro: quantidade de colunas e valores diferentes";

    for(int i = 0; i < values.size(); i++)
        values[i] = "'" + values[i] + "'";

    string sql = "INSERT INTO " + tableName + this->encapsulateVector(columns);
    sql += " VALUES" + this->encapsulateVector(values);
    this->endSql(sql);

    if(log) this->log->info(sql);

    char* err;
    if(sqlite3_exec(this->db, sql.c_str(), NULL, 0, &err) != SQLITE_OK){
        if(this->log != nullptr) this->log->error(err);
        std::cerr << "Erro ao inserir: " << err << std::endl;
    }
}

int DatabaseManager::select_callback(void* data, int argc, char** argv, char** colNames){
    vector<vector<string>>* results = (vector<vector<string>>*)data;
    vector<string> row;

    for(int i = 0; i < argc; i++) row.push_back(argv[i]);
    results->push_back(row);

    return 0;
}

string DatabaseManager::join_strings(const vector<string>& vec, const string& delimiter){
    string result;
    for (size_t i = 0; i < vec.size(); i++) {
        result += vec[i];
        if (i < vec.size() - 1) {
            result += delimiter;
        }
    }
    return result;
}

vector<vector<string>> DatabaseManager::select(const string& tableName, const vector<string>& columns, bool log){
    vector<vector<string>> results;

    string sql = "SELECT " + join_strings(columns, ",") + " FROM " + tableName + ";";

    if(log) this->log->info(sql);

    char* err = nullptr;
    if (sqlite3_exec(this->db, sql.c_str(), select_callback, &results, &err) != SQLITE_OK) {
        std::cerr << "Erro ao executar consulta: " << err << "\n";
        if(this->log != nullptr) this->log->error(err);
    }

    return results;
}