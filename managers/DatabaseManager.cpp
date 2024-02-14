#include "DatabaseManager.h"
#include <iostream>
#include <fstream>
#include <ctime>

const std::string Log::logPath = "db.log";

void Log::clear(){
    std::ofstream file(Log::logPath, std::ios::out | std::ios::trunc);
    if (!file.is_open()) return;
    file.close();
}

void Log::info(std::string message){
    std::ofstream file(Log::logPath, std::ios::out | std::ios::app);
    if (!file.is_open()) return;

    time_t currentTime = time(nullptr);
    tm* localTime = localtime(&currentTime);

    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localTime);

    file << "[" << timestamp << "] [INFO] " << message << std::endl;
    file.close();
}

void Log::error(string message){
    std::ofstream file(Log::logPath, std::ios::out | std::ios::app);
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

inline sqlite3* DatabaseManager::create_sqlite(){
    sqlite3* db;
    if(sqlite3_open(this->dbPath, &db) != SQLITE_OK)
        throw "Erro ao abrir o banco de dados";
    return db;
}

void DatabaseManager::dropTable(const string &tableName){
    string sql = "DROP TABLE IF EXISTS " + tableName;
    this->endSql(sql);

    Log::info(sql);

    sqlite3* db = create_sqlite();

    char* err;
    if(sqlite3_exec(db, sql.c_str(), NULL, 0, &err) != SQLITE_OK){
        Log::error(err);
        std::cerr << "Erro ao deletar tabela: " << err << std::endl;
    }

    sqlite3_close(db);
}

DatabaseManager::DatabaseManager(){
    Log::clear();
}

void DatabaseManager::createTable(const string& tableName, vector<string> columns, vector<string> types){
    if(columns.size() != types.size())
        throw "Erro: quantidade de colunas e tipos diferentes";

    vector<string> columnsTypes;
    for(int i = 0; i < columns.size(); i++)
        columnsTypes.push_back(columns[i] + " " + types[i]);

    string sql = "CREATE TABLE IF NOT EXISTS " + tableName + encapsulateVector(columnsTypes);
    this->endSql(sql);

    Log::info(sql);

    sqlite3* db = create_sqlite();

    char* err;
    if(sqlite3_exec(db, sql.c_str(), NULL, 0, &err) != SQLITE_OK){
        Log::error(err);
        std::cerr << "Erro ao criar tabela: " << err << std::endl;
    }

    sqlite3_close(db);
}

void DatabaseManager::insert(const string& tableName, vector<string> columns, vector<string> values, bool log){
    if(columns.size() != values.size())
        throw "Erro: quantidade de colunas e valores diferentes";

    for(int i = 0; i < values.size(); i++)
        values[i] = "'" + values[i] + "'";

    string sql = "INSERT INTO " + tableName + this->encapsulateVector(columns);
    sql += " VALUES" + this->encapsulateVector(values);
    this->endSql(sql);

    if(log) Log::info(sql);

    sqlite3* db = create_sqlite();
    
    char* err;
    if(sqlite3_exec(db, sql.c_str(), NULL, 0, &err) != SQLITE_OK){
        Log::error(err);
        std::cerr << "Erro ao inserir: " << err << std::endl;
    }

    sqlite3_close(db);
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

    if(log) Log::info(sql);

    sqlite3* db = create_sqlite();

    char* err = nullptr;
    if (sqlite3_exec(db, sql.c_str(), select_callback, &results, &err) != SQLITE_OK) {
        std::cerr << "Erro ao executar consulta: " << err << "\n";
        Log::error(err);
    }

    return results;
}