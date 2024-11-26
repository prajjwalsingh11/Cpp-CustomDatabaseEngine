#include "StorageEngine.h"
#include <cassert>
#include <iostream>

void testStorageEngineFactory() {
    StorageEngine* memoryStorage = StorageEngineFactory::createStorageEngine("memory");
    assert(memoryStorage != nullptr && "Factory failed to create memory storage engine");

    StorageEngine* fileStorage = StorageEngineFactory::createStorageEngine("file");
    assert(fileStorage != nullptr && "Factory failed to create file storage engine");

    // Test that the correct types are created (memory or file storage)
    // You can expand this check further to validate behavior, if needed.

    std::cout << "Factory pattern test passed!" << std::endl;

    delete memoryStorage;
    delete fileStorage;
}

int main() {
    testStorageEngineFactory();
    return 0;
}
