#include "DatabaseEngine.h"
#include <cassert>
#include <iostream>

void testSingleton() {
    // Get two instances of DatabaseEngine
    DatabaseEngine& db1 = DatabaseEngine::getInstance();
    DatabaseEngine& db2 = DatabaseEngine::getInstance();

    // Ensure that both instances are the same (Singleton pattern)
    assert(&db1 == &db2 && "Singleton failed: Instances are not the same");

    std::cout << "Singleton test passed!" << std::endl;
}

int main() {
    testSingleton();
    return 0;
}
