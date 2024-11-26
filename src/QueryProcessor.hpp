#ifndef QUERYPROCESSOR_HPP
#define QUERYPROCESSOR_HPP

#include "StorageEngine.hpp"

class QueryProcessor {
public:
    explicit QueryProcessor(StorageEngine* engine);
    void executeQuery(const std::string& query);
    void executeSelect(const std::string& query);
    void executeInsert(const std::string& query);

private:
    StorageEngine* storageEngine;
};

#endif // QUERYPROCESSOR_HPP
