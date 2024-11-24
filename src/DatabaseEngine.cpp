// DatabaseEngine.h
// Singleton Pattern
#pragma once
#include <string>
#include <iostream>
using namespace std;

class DatabaseEngine {
public:
    static DatabaseEngine& getInstance() {
        static DatabaseEngine instance; // Guaranteed to be destroyed, instantiated on first use.
        return instance;
    }

    void start() {
        // Initialize the database engine
        cout << "Database Engine Started" << endl;
    }

    void executeQuery(const string& query) {
        // Logic to execute query
        cout << "Executing query: " << query << endl;
    }

private:
    DatabaseEngine() = default;
    ~DatabaseEngine() = default;

    // Prevent copy constructor and assignment operator
    DatabaseEngine(const DatabaseEngine&) = delete;
    DatabaseEngine& operator=(const DatabaseEngine&) = delete;
};
