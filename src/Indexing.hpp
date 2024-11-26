#ifndef INDEXING_HPP
#define INDEXING_HPP

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

// Base class for indexing strategies
class IndexStrategy {
public:
    virtual ~IndexStrategy() = default;

    // Add an index entry (specific to the strategy)
    virtual void addIndexEntry(const std::string& key, int rowId) = 0;

    // Retrieve the row IDs for a given index key (specific to the strategy)
    virtual std::vector<int> getIndexEntries(const std::string& key) const = 0;

    // Check if an index entry exists
    virtual bool hasIndexEntry(const std::string& key) const = 0;
};

// Hash Index Strategy
class HashIndex : public IndexStrategy {
public:
    void addIndexEntry(const std::string& key, int rowId) override;
    std::vector<int> getIndexEntries(const std::string& key) const override;
    bool hasIndexEntry(const std::string& key) const override;

private:
    std::unordered_map<std::string, std::vector<int>> indexData;
};

// B-Tree Index Strategy (simplified version)
class BTreeIndex : public IndexStrategy {
public:
    void addIndexEntry(const std::string& key, int rowId) override;
    std::vector<int> getIndexEntries(const std::string& key) const override;
    bool hasIndexEntry(const std::string& key) const override;

private:
    // Placeholder for B-tree node structure (simplified)
    std::unordered_map<std::string, std::vector<int>> indexData;
};

// Index class that uses different strategies
class Index {
public:
    // Constructor to choose the strategy
    Index(const std::string& columnName, std::unique_ptr<IndexStrategy> strategy);

    // Add data to the index using the strategy
    void addIndexEntry(const std::string& key, int rowId);

    // Retrieve row IDs for a given index key using the strategy
    std::vector<int> getIndexEntries(const std::string& key) const;

    // Check if an index entry exists for the key
    bool hasIndexEntry(const std::string& key) const;

    // Get the column name this index is based on
    std::string getColumnName() const;

private:
    std::string columnName;
    std::unique_ptr<IndexStrategy> indexStrategy;  // The strategy used for indexing
};

#endif // INDEXING_HPP
