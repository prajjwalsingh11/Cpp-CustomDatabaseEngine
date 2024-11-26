
# Design Patterns in the C++ Database Engine

This document outlines the various **design patterns** employed in the development of the C++ Database Engine. It describes how each pattern enhances the system's flexibility, scalability, and maintainability by decoupling components and providing reusable solutions for common design problems.

---

## 1. Singleton Pattern

### **Pattern Description:**

The **Singleton pattern** ensures that a class has only one instance and provides a global access point to that instance. In our system, the `DatabaseEngine` is designed as a Singleton to manage the state of the database engine and ensure there is only one instance controlling access to the database and transactions.

### **Why Singleton?**
- **Global Access:** The Singleton ensures that the `DatabaseEngine` is globally accessible from any part of the application without the need for multiple instances.
- **State Management:** It helps in managing the database’s initialization state. By using a Singleton, we ensure the database is initialized only once and used consistently across the system.

### **Implementation:**

```cpp
class DatabaseEngine {
public:
    // Get the singleton instance of DatabaseEngine
    static DatabaseEngine& getInstance() {
        static DatabaseEngine instance;  // Local static variable ensures single instance
        return instance;
    }

    // Deleted copy constructor and assignment operator to prevent copies
    DatabaseEngine(const DatabaseEngine&) = delete;
    DatabaseEngine& operator=(const DatabaseEngine&) = delete;

private:
    // Constructor, destructor and other private methods
    DatabaseEngine();
    ~DatabaseEngine();
};
```

In this implementation, the static `getInstance()` method ensures that the `DatabaseEngine` object is created only once. The copy constructor and assignment operator are deleted to prevent accidental copying.

---

## 2. Strategy Pattern

### **Pattern Description:**

The **Strategy pattern** defines a family of algorithms, encapsulates each one, and makes them interchangeable. The `StorageEngine` uses the Strategy pattern to manage different types of storage systems (like memory-based or file-based) without modifying the core logic of the database engine.

### **Why Strategy?**
- **Flexibility:** The database engine can easily switch between different storage strategies at runtime.
- **Encapsulation:** Each storage backend (e.g., in-memory, file-based) is encapsulated within its own class, making the system extensible and maintainable.

### **Implementation:**

```cpp
// Abstract class for different storage backends
class StorageBackend {
public:
    virtual void storeData(const std::string& data) = 0;
    virtual std::vector<std::string> retrieveData() = 0;
    virtual ~StorageBackend() = default;
};

// In-memory storage strategy
class MemoryStorage : public StorageBackend {
public:
    void storeData(const std::string& data) override;
    std::vector<std::string> retrieveData() override;
};

// File-based storage strategy
class FileStorage : public StorageBackend {
public:
    void storeData(const std::string& data) override;
    std::vector<std::string> retrieveData() override;
};
```

In this implementation, `StorageBackend` is an abstract class, and different storage strategies like `MemoryStorage` and `FileStorage` are concrete implementations of this strategy.

---

## 3. State Pattern

### **Pattern Description:**

The **State pattern** allows an object to change its behavior when its internal state changes. In the `TransactionManager` class, the State pattern is used to manage the states of a transaction (e.g., active, committed, aborted) and ensure that the system behaves accordingly.

### **Why State?**
- **State Management:** By separating the logic associated with each state (e.g., active, committed, aborted) into individual classes, the code becomes cleaner, more maintainable, and easier to extend.
- **Flexible Transitions:** State transitions are simplified, allowing for easy and reliable switching between states.

### **Implementation:**

```cpp
class TransactionState {
public:
    virtual void handle(TransactionManager* manager) = 0;
};

class ActiveState : public TransactionState {
public:
    void handle(TransactionManager* manager) override {
        // Handle active state transaction
    }
};

class CommittedState : public TransactionState {
public:
    void handle(TransactionManager* manager) override {
        // Handle committed transaction
    }
};

class AbortedState : public TransactionState {
public:
    void handle(TransactionManager* manager) override {
        // Handle aborted transaction
    }
};
```

Here, each `TransactionState` (e.g., `ActiveState`, `CommittedState`, `AbortedState`) encapsulates the logic for a specific state of the transaction, and the `TransactionManager` can easily transition between these states by changing the current state.

---

## 4. Command Pattern

### **Pattern Description:**

The **Command pattern** encapsulates a request as an object, which allows for the parameterization of clients with queues, requests, and operations. In our system, the `QueryProcessor` utilizes the Command pattern to process SQL queries by encapsulating each command as an object.

### **Why Command?**
- **Decoupling:** The Command pattern decouples the sender of a request from the object that executes it, making the code modular and easier to extend.
- **Queue Management:** The pattern facilitates command queuing, logging, and transactional behavior, ensuring operations are executed in a controlled manner.

### **Implementation:**

```cpp
class Command {
public:
    virtual void execute() = 0;  // Interface to execute commands
};

class InsertCommand : public Command {
public:
    void execute() override {
        // Insert SQL command logic
    }
};

class QueryProcessor {
public:
    void processCommand(Command* command) {
        command->execute();
    }
};
```

Here, `Command` defines an abstract interface for various SQL commands (e.g., `InsertCommand`), and the `QueryProcessor` executes these commands when processed.

---

## 5. Factory Method Pattern

### **Pattern Description:**

The **Factory Method pattern** defines an interface for creating objects but allows subclasses to alter the type of objects that will be created. The `DatabaseEngine` uses a factory method for creating instances of `StorageEngine` based on the selected backend type (e.g., file-based or in-memory storage).

### **Why Factory Method?**
- **Object Creation Control:** The Factory method provides a flexible way to create objects at runtime based on input parameters, without coupling the creation logic to the concrete classes.
- **Extensibility:** New storage types can be added easily by creating new subclasses of `StorageEngine`, making the system extensible.

### **Implementation:**

```cpp
class StorageEngineFactory {
public:
    static StorageEngine* createStorageEngine(const std::string& type) {
        if (type == "memory") {
            return new MemoryStorage();
        } else if (type == "file") {
            return new FileStorage("database.txt");
        }
        return nullptr;
    }
};
```

In this pattern, the `StorageEngineFactory` decides which storage backend to instantiate based on the input type, making it easy to add more storage strategies in the future.

---

## 6. Observer Pattern (Optional)

### **Pattern Description:**

The **Observer pattern** is used to allow an object (the subject) to notify a set of dependent objects (observers) about changes in its state. Although not implemented explicitly in this system, it could be useful for notifying other parts of the application (such as UI or logging systems) when a transaction state changes (e.g., from active to committed or aborted).

### **Why Observer?**
- **Decoupled Communication:** It allows components to subscribe to transaction state changes without coupling them to the transaction management logic.
- **Event-driven Architecture:** The observer pattern is useful for handling events in an asynchronous manner.

---

## Summary of Design Patterns

| **Design Pattern**   | **Class Example**        | **Purpose**                                                                 |
|----------------------|--------------------------|-----------------------------------------------------------------------------|
| Singleton            | `DatabaseEngine`          | Ensures a single global instance of the database engine.                     |
| Strategy             | `StorageEngine`           | Allows dynamic swapping between different storage backends (memory, file).   |
| State                | `TransactionManager`      | Allows the transaction state (active, committed, aborted) to change behavior dynamically. |
| Command              | `QueryProcessor`          | Encapsulates SQL commands as objects for decoupling command execution logic. |
| Factory Method       | `StorageEngineFactory`    | Provides a way to create instances of storage backends without exposing their concrete classes. |
| Observer             | (Optional)                | Provides a way to notify components when transaction states change.          |

---

## Conclusion

By employing these design patterns, the C++ Database Engine maintains flexibility, modularity, and scalability. Each pattern serves to decouple different concerns in the system, making it easier to extend and maintain the codebase. The combination of Singleton, Strategy, State, Command, and Factory Method patterns ensures that the system remains robust and adaptable to future requirements.
