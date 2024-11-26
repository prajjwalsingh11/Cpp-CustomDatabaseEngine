#ifndef DATABASEENGINE_HPP
#define DATABASEENGINE_HPP

#include <string>
#include <unordered_map>
#include <memory>
#include "StorageEngine.hpp"
#include "QueryProcessor.hpp"
#include "TransactionManager.hpp"

class DatabaseEngine {
public:
    // Constructor
    DatabaseEngine();

    // Methods for initializing, table creation, inserting data, and querying
    void initializeDatabase(const std::string& dbPath = "");
    void createTable(const std::string& tableDefinition);
    void insertData(const std::string& insertStatement);
    void executeQuery(const std::string& query);

    // Transaction management
    void startTransaction();
    void commitTransaction();
    void rollbackTransaction();

    // Storage Engine Setup
    void setStorageEngine(const std::string& storageType);

    // Destructor
    ~DatabaseEngine();

private:
    // Components of the database engine
    StorageEngine* storageEngine;
    QueryProcessor* queryProcessor;
    TransactionManager* transactionManager;

    // Table storage (for simulation purposes)
    std::unordered_map<std::string, std::string> tables;

    // Flag to ensure database is initialized
    bool initialized;
};

#endif // DATABASEENGINE_HPP