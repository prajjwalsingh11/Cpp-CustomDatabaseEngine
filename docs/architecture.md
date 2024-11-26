# Architecture Overview

The architecture of the C++ Database Engine is designed to be modular, with the flexibility to support various backend storage solutions and transaction management. The main components include:

### Key Components:
- **DatabaseEngine**: The core class that initializes and manages the database engine. It interacts with the storage, query processor, and transaction manager.
- **StorageEngine**: A wrapper for different storage backends such as memory and file storage.
- **TransactionManager**: Manages transaction states and controls commit/rollback mechanisms.
- **QueryProcessor**: Responsible for parsing and executing SQL queries.

### Diagram: 

```plaintext
+--------------------------------+
|         DatabaseEngine         |
|--------------------------------|
| - storageEngine                |
| - queryProcessor               |
| - transactionManager           |
+--------------------------------+
           | | |
   +------------------+-----------------+
   |                  |                 |
+---------+    +-------------+   +----------------+
|Storage  |    |QueryProcessor|   |TransactionManager|
|Engine   |    |             |   |                |
+---------+    +-------------+   +----------------+
