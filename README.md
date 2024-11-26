
# Usage of C++ Database Engine

This document provides an example of how to use the C++ Database Engine, showcasing various components such as the `DatabaseEngine`, `TransactionManager`, `QueryProcessor`, and `StorageEngine`. The goal is to demonstrate how to initialize the database, interact with tables, and perform basic operations.

## Prerequisites

- A C++ compiler supporting C++11 or later.
- SQLite3 library installed for database support (optional for certain parts).
- `pybind11` for Python bindings (optional for Python integration).

## Setup Instructions

### 1. Installing Dependencies

- For SQLite3, ensure you have SQLite3 installed on your system.
  - On Linux: `sudo apt-get install libsqlite3-dev`
  - On macOS: `brew install sqlite3`
  - On Windows: Download and install SQLite from the official website.

- To use Python bindings, install `pybind11`:
  ```bash
  pip install pybind11
  ```

### 2. Building the Project

To build the project, use CMake. Follow these steps:

```bash
mkdir build
cd build
cmake ..
make
```

This will build the C++ project along with the Python bindings (if enabled).

## Example Usage

### 1. Initializing the Database

```cpp
#include "DatabaseEngine.hpp"

int main() {
    // Get the singleton instance of DatabaseEngine
    DatabaseEngine& dbEngine = DatabaseEngine::getInstance();

    // Initialize the database with a file path
    dbEngine.initializeDatabase("example.db");

    // Set the storage engine (memory or file-based)
    dbEngine.setStorageEngine("file");
}
```

### 2. Creating a Table

```cpp
// Create a table in the database
std::string tableDefinition = "CREATE TABLE users (id INTEGER PRIMARY KEY, name TEXT, age INTEGER);";
dbEngine.createTable(tableDefinition);
```

### 3. Inserting Data

```cpp
// Insert data into the database
std::string insertStatement = "INSERT INTO users (id, name, age) VALUES (1, 'Alice', 30);";
dbEngine.insertData(insertStatement);
```

### 4. Executing a Query

```cpp
// Execute a SQL query
std::string query = "SELECT * FROM users;";
dbEngine.executeQuery(query);
```

### 5. Transaction Management

#### Starting a Transaction

```cpp
dbEngine.startTransaction();
```

#### Committing a Transaction

```cpp
dbEngine.commitTransaction();
```

#### Rolling Back a Transaction

```cpp
dbEngine.rollbackTransaction();
```

### 6. Python Bindings Usage

If you have enabled the Python bindings, you can interact with the database engine directly from Python:

```python
import database_engine

# Get the singleton instance
db = database_engine.DatabaseEngine.getInstance()

# Initialize the database
db.initializeDatabase("example.db")

# Set the storage engine
db.setStorageEngine("file")

# Create a table
table_definition = "CREATE TABLE users (id INTEGER PRIMARY KEY, name TEXT, age INTEGER);"
db.createTable(table_definition)

# Insert data
insert_statement = "INSERT INTO users (id, name, age) VALUES (1, 'Alice', 30);"
db.insertData(insert_statement)

# Execute a query
query = "SELECT * FROM users;"
db.executeQuery(query)

# Start a transaction
db.startTransaction()

# Commit the transaction
db.commitTransaction()
```

## Conclusion

This usage guide provides the basic steps for initializing and interacting with the C++ Database Engine. The example demonstrates how to initialize the database, create tables, insert data, execute queries, and manage transactions.

For more advanced features and details, refer to the full documentation and codebase.
