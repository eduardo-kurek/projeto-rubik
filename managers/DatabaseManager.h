#pragma once

#include "../sqlite/sqlite3.h"
#include <string>
#include <vector>
#include <iostream>

using string = std::string;

template<typename T>
using vector = std::vector<T>;

class Log{

    static const string logPath;

    public:
    static void clear();
    static void info(string message);
    static void error(string message);

};

class DatabaseManager{

    const char* dbPath = "rubik.db";

    inline string encapsulateVector(vector<string> columns);
    inline void endSql(string& sql);
    inline sqlite3* create_sqlite();

    static int insert_callback(void* data, int argc, char** argv, char** colNames);
    string join_strings(const vector<string>& vec, const string& delimiter);

    public:
    DatabaseManager();
    void createTable(const string& tableName, vector<string> columns, vector<string> types);
    void dropTable(const string& tableName);
    void insert(const string& tableName, vector<string> columns, vector<string> values, bool log = false);
    vector<vector<string>> select(const string& tableName, const vector<string>& columns, bool log = false);
    
};