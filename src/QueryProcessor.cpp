#include "QueryProcessor.hpp"
#include <iostream>

QueryProcessor::QueryProcessor(StorageEngine* engine) : storageEngine(engine) {}

void QueryProcessor::executeQuery(const std::string& query) {
    std::cout << "Executing query: " << query << std::endl;
    // Basic query routing (for now, assuming SELECT or INSERT)
    if (query.find("SELECT") != std::string::npos) {
        executeSelect(query);
    } else if (query.find("INSERT") != std::string::npos) {
        executeInsert(query);
    }
}

void QueryProcessor::executeSelect(const std::string& query) {
    std::cout << "Executing SELECT query: " << query << std::endl;

    // Simulate SELECT query (searching an index)
    std::string column = "name";  // Example column
    std::string value = "Alice";  // Example value to search
    auto results = storageEngine->searchIndex(value);

    for (const auto& result : results) {
        std::cout << "Result: " << result << std::endl;
    }
}

void QueryProcessor::executeInsert(const std::string& query) {
    std::cout << "Executing INSERT query: " << query << std::endl;
    storageEngine->storeData(query);  // Simulate insert
}
