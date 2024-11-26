#ifndef TRANSACTIONDATA_HPP
#define TRANSACTIONDATA_HPP

#include <vector>
#include <string>

class TransactionData {
public:
    std::vector<std::string> changes;  // List of changes (SQL queries)

    void addChange(const std::string& change) {
        changes.push_back(change);  // Add a change (e.g., SQL query)
    }
};

#endif // TRANSACTIONDATA_HPP
