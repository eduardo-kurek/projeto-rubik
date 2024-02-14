#pragma once

#include "../sqlite/sqlite3.h"
#include <string>
#include <vector>
#include <iostream>

using string = std::string;

template<typename T>
using vector = std::vector<T>;

class Log{

    string relativePath;

    public:
    Log(string relativePath);
    void clear();
    void info(string message);
    void error(string message);

};

class DatabaseManager{

    string dbPath;
    sqlite3* db;
    Log* log = nullptr;

    inline string encapsulateVector(vector<string> columns);
    inline void endSql(string& sql);

    static int select_callback(void* data, int argc, char** argv, char** colNames);
    string join_strings(const vector<string>& vec, const string& delimiter);

    public:
    DatabaseManager(string dbPath = "rubik.db");
    DatabaseManager(Log* log, string dbPath = "rubik.db");
    ~DatabaseManager();
    void createTable(const string& tableName, vector<string> columns, vector<string> types);
    void dropTable(const string& tableName);
    void insert(const string& tableName, vector<string> columns, vector<string> values, bool log = false);
    vector<vector<string>> select(const string& tableName, const vector<string>& columns, bool log = false);
    
};