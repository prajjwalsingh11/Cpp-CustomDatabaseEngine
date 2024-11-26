#ifndef STORAGEENGINE_HPP
#define STORAGEENGINE_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

// Abstract class for data storage (Base class for different backends)
class StorageBackend {
public:
    virtual ~StorageBackend() = default;
    virtual void storeData(const std::string& data) = 0;
    virtual std::vector<std::string> retrieveData() = 0;
};

// MemoryStorage: In-memory storage backend
class MemoryStorage : public StorageBackend {
public:
    void storeData(const std::string& data) override;
    std::vector<std::string> retrieveData() override;

private:
    std::vector<std::string> memoryData;  // In-memory data storage
};

// FileStorage: File-based storage backend
class FileStorage : public StorageBackend {
public:
    explicit FileStorage(const std::string& file);
    void storeData(const std::string& data) override;
    std::vector<std::string> retrieveData() override;

private:
    std::string filename;  // File where data is stored
};

// StorageEngine: The main class that manages different storage backends
class StorageEngine {
public:
    explicit StorageEngine(const std::string& backendType);
    ~StorageEngine();

    void storeData(const std::string& data);
    std::vector<std::string> retrieveData();

    void createIndex(const std::string& column);
    std::vector<std::string> searchIndex(const std::string& value);

private:
    StorageBackend* backend;
    std::unordered_map<std::string, std::vector<std::string>> index;  // Simple index structure
};

#endif // STORAGEENGINE_HPP