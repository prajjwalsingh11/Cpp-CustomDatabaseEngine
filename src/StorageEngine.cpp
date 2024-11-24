// StorageEngine.h
// factory pattern
#pragma once
#include <string>
#include <iostream>
using namespace std;

class StorageEngine {
public:
    virtual void save(const string& data) = 0;
    virtual string load(const string& key) = 0;
    virtual ~StorageEngine() = default;
};

class MemoryStorageEngine : public StorageEngine {
public:
    void save(const string& data) override {
        cout << "Saving data to memory: " << data << endl;
    }

    string load(const string& key) override {
        return "Loaded data from memory";
    }
};

class FileStorageEngine : public StorageEngine {
public:
    void save(const string& data) override {
        cout << "Saving data to file: " << data << endl;
    }

    string load(const string& key) override {
        return "Loaded data from file";
    }
};
