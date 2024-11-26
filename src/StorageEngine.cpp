#include "StorageEngine.hpp"
#include <iostream>
#include <fstream>

// MemoryStorage Implementation
void MemoryStorage::storeData(const std::string& data) {
    memoryData.push_back(data);
    std::cout << "Data stored in memory: " << data << std::endl;
}

std::vector<std::string> MemoryStorage::retrieveData() {
    std::cout << "Retrieving data from memory." << std::endl;
    return memoryData;
}

// FileStorage Implementation
FileStorage::FileStorage(const std::string& file) : filename(file) {}

void FileStorage::storeData(const std::string& data) {
    std::ofstream outfile(filename, std::ios::app);
    if (outfile.is_open()) {
        outfile << data << std::endl;
        std::cout << "Data stored in file: " << filename << std::endl;
        outfile.close();
    } else {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
    }
}

std::vector<std::string> FileStorage::retrieveData() {
    std::vector<std::string> fileData;
    std::ifstream infile(filename);
    std::string line;
    if (infile.is_open()) {
        while (std::getline(infile, line)) {
            fileData.push_back(line);
        }
        infile.close();
    } else {
        std::cerr << "Error: Unable to open file for reading." << std::endl;
    }
    std::cout << "Data retrieved from file: " << filename << std::endl;
    return fileData;
}

// StorageEngine Implementation
StorageEngine::StorageEngine(const std::string& backendType) {
    if (backendType == "memory") {
        backend = new MemoryStorage();
    } else if (backendType == "file") {
        backend = new FileStorage("database.txt");
    } else {
        throw std::invalid_argument("Unknown backend type: " + backendType);
    }
}

StorageEngine::~StorageEngine() {
    delete backend;
}

void StorageEngine::storeData(const std::string& data) {
    backend->storeData(data);
}

std::vector<std::string> StorageEngine::retrieveData() {
    return backend->retrieveData();
}

void StorageEngine::createIndex(const std::string& column) {
    std::cout << "Index created for column: " << column << std::endl;
    // Example indexing logic (in a real-world scenario, you'd index the data)
    index[column] = {};  // Initialize empty index for the column
}

std::vector<std::string> StorageEngine::searchIndex(const std::string& value) {
    std::vector<std::string> results;
    // Search index for a value (simple example)
    for (const auto& [key, entries] : index) {
        for (const auto& entry : entries) {
            if (entry == value) {
                results.push_back(entry);
            }
        }
    }
    return results;
}
