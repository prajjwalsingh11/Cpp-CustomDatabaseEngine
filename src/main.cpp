#include <iostream>
#include "DatabaseEngine.hpp"

int main() {
    // Step 1: Initialize the Database Engine
    DatabaseEngine dbEngine;
    dbEngine.initializeDatabase("example.db");

    // Step 2: Set Storage Engine (e.g., In-memory or file-based)
    dbEngine.setStorageEngine("memory");

    // Step 3: Create a Table
    std::string tableDefinition = "CREATE TABLE users (id INT, name TEXT, age INT);";
    dbEngine.createTable(tableDefinition);

    // Step 4: Insert Data into the Table
    std::string insertQuery = "INSERT INTO users VALUES (1, 'Alice', 30);";
    dbEngine.insertData(insertQuery);
    insertQuery = "INSERT INTO users VALUES (2, 'Bob', 25);";
    dbEngine.insertData(insertQuery);

    // Step 5: Start a Transaction
    std::cout << "Starting Transaction..." << std::endl;
    dbEngine.startTransaction();

    // Step 6: Execute Query During Transaction
    std::cout << "Executing query during transaction..." << std::endl;
    dbEngine.executeQuery("SELECT * FROM users;");

    // Step 7: Commit the Transaction
    std::cout << "Committing Transaction..." << std::endl;
    dbEngine.commitTransaction();

    // Step 8: Perform Rollback Transaction (Just an example)
    std::cout << "Starting another transaction..." << std::endl;
    dbEngine.startTransaction();

    // Step 9: Insert additional data and then rollback
    dbEngine.insertData("INSERT INTO users VALUES (3, 'Charlie', 22);");
    dbEngine.rollbackTransaction();

    // Step 10: Final Query after Rollback (Data should not include 'Charlie')
    std::cout << "Executing query after rollback (should not show Charlie)..." << std::endl;
    dbEngine.executeQuery("SELECT * FROM users;");

    return 0;
}
