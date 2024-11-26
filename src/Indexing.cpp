#include "Indexing.hpp"
#include <iostream>
#include <unordered_map>

// HashIndex Implementation
void HashIndex::addIndexEntry(const std::string& key, int rowId) {
    indexData[key].push_back(rowId);
    std::cout << "Hash Index: Added entry [" << key << "] -> Row ID: " << rowId << std::endl;
}

std::vector<int> HashIndex::getIndexEntries(const std::string& key) const {
    auto it = indexData.find(key);
    if (it != indexData.end()) {
        return it->second;
    }
    return {};  // Return empty vector if key not found
}

bool HashIndex::hasIndexEntry(const std::string& key) const {
    return indexData.find(key) != indexData.end();
}

// BTreeIndex Implementation (simplified version)
void BTreeIndex::addIndexEntry(const std::string& key, int rowId) {
    indexData[key].push_back(rowId);
    std::cout << "B-Tree Index: Added entry [" << key << "] -> Row ID: " << rowId << std::endl;
}

std::vector<int> BTreeIndex::getIndexEntries(const std::string& key) const {
    auto it = indexData.find(key);
    if (it != indexData.end()) {
        return it->second;
    }
    return {};  // Return empty vector if key not found
}

bool BTreeIndex::hasIndexEntry(const std::string& key) const {
    return indexData.find(key) != indexData.end();
}

// Index Class Implementation
Index::Index(const std::string& columnName, std::unique_ptr<IndexStrategy> strategy)
    : columnName(columnName), indexStrategy(std::move(strategy)) {}

void Index::addIndexEntry(const std::string& key, int rowId) {
    indexStrategy->addIndexEntry(key, rowId);
}

std::vector<int> Index::getIndexEntries(const std::string& key) const {
    return indexStrategy->getIndexEntries(key);
}

bool Index::hasIndexEntry(const std::string& key) const {
    return indexStrategy->hasIndexEntry(key);
}

std::string Index::getColumnName() const {
    return columnName;
}
