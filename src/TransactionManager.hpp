#ifndef TRANSACTIONMANAGER_HPP
#define TRANSACTIONMANAGER_HPP

#include <vector>
#include <string>
#include <iostream>
#include "TransactionData.hpp"
#include "StorageEngine.hpp"

// Forward declarations of state classes
class TransactionManager;
class TransactionState;
class TransactionData;
class StorageEngine;

// Abstract TransactionState class
class TransactionState {
public:
    virtual ~TransactionState() = default;
    virtual void handle(TransactionManager* manager) = 0;
};

// TransactionManager class
class TransactionManager {
private:
    TransactionState* currentState;  // Current state of the transaction
    TransactionData* transactionData;  // Data associated with the transaction
    StorageEngine* storageEngine;  // The storage engine managing the database
public:

    TransactionManager(StorageEngine* engine);
    ~TransactionManager();

    void setState(TransactionState* state);  // Set the transaction state
    void handleTransaction();  // Handle the transaction

    void setTransactionData(TransactionData* data);  // Set transaction data
    TransactionData* getTransactionData();  // Get transaction data

    StorageEngine* getStorageEngine();  // Get the storage engine
};

// ActiveState class
class ActiveState : public TransactionState {
public:
    void handle(TransactionManager* manager) override;
    void lockResources(TransactionManager* manager);  // Lock resources
    void trackChanges(TransactionManager* manager);  // Track changes during transaction
};

// CommittedState class
class CommittedState : public TransactionState {
public:
    void handle(TransactionManager* manager) override;
    void applyChanges(TransactionManager* manager);  // Apply changes to the database
    void releaseLocks(TransactionManager* manager);  // Release locks after commit
};

// AbortedState class
class AbortedState : public TransactionState {
public:
    void handle(TransactionManager* manager) override;
    void rollbackChanges(TransactionManager* manager);  // Rollback changes
    void releaseLocks(TransactionManager* manager);  // Release locks after abort
};

#endif // TRANSACTIONMANAGER_HPP
