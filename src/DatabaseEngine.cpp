#include "DatabaseEngine.hpp"
#include <iostream>
#include <sqlite3.h>

// Constructor
DatabaseEngine::DatabaseEngine() 
    : storageEngine(nullptr), queryProcessor(new QueryProcessor()), transactionManager(new TransactionManager()), initialized(false) {
}

// Destructor
DatabaseEngine::~DatabaseEngine() {
    delete storageEngine;
    delete queryProcessor;
    delete transactionManager;
}

// Initialize Database Engine (opens SQLite DB if path is provided)
void DatabaseEngine::initializeDatabase(const std::string& dbPath) {
    // Only initialize once
    if (initialized) {
        std::cerr << "Database is already initialized!" << std::endl;
        return;
    }

    sqlite3* db;
    int rc = sqlite3_open(dbPath.c_str(), &db); // Creates the DB if it doesn't exist
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    } else {
        std::cout << "Opened database successfully!" << std::endl;
    }
    sqlite3_close(db);
    initialized = true;
}

// Create a table in the database (simulated for now)
void DatabaseEngine::createTable(const std::string& tableDefinition) {
    if (!initialized) {
        std::cerr << "Database not initialized!" << std::endl;
        return;
    }

    std::cout << "Creating table with definition: " << tableDefinition << std::endl;
    tables["table_name"] = tableDefinition;  // Simulate table creation
}

// Insert data into the database (simulated storage)
void DatabaseEngine::insertData(const std::string& insertStatement) {
    if (!initialized) {
        std::cerr << "Database not initialized!" << std::endl;
        return;
    }

    std::cout << "Inserting data: " << insertStatement << std::endl;
    storageEngine->storeData(insertStatement);
}

// Execute a query (delegates to QueryProcessor)
void DatabaseEngine::executeQuery(const std::string& query) {
    if (!initialized) {
        std::cerr << "Database not initialized!" << std::endl;
        return;
    }

    std::cout << "Executing query: " << query << std::endl;
    queryProcessor->executeQuery(query);
}

// Start a transaction (delegates to TransactionManager)
void DatabaseEngine::startTransaction() {
    if (!initialized) {
        std::cerr << "Database not initialized!" << std::endl;
        return;
    }

    std::cout << "Starting transaction." << std::endl;
    transactionManager->setState(new ActiveState());
}

// Commit the transaction (delegates to TransactionManager)
void DatabaseEngine::commitTransaction() {
    if (!initialized) {
        std::cerr << "Database not initialized!" << std::endl;
        return;
    }

    std::cout << "Committing transaction." << std::endl;
    transactionManager->setState(new CommittedState());
    transactionManager->handleTransaction();
}

// Rollback the transaction (delegates to TransactionManager)
void DatabaseEngine::rollbackTransaction() {
    if (!initialized) {
        std::cerr << "Database not initialized!" << std::endl;
        return;
    }

    std::cout << "Rolling back transaction." << std::endl;
    transactionManager->setState(new AbortedState());
    transactionManager->handleTransaction();
}

// Set the storage engine type (memory, file, etc.)
void DatabaseEngine::setStorageEngine(const std::string& storageType) {
    storageEngine = new StorageEngine(storageType);
}
