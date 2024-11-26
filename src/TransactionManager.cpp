#include "TransactionManager.hpp"
#include "StorageEngine.hpp"
#include <iostream>

// TransactionManager Implementation
TransactionManager::TransactionManager(StorageEngine* engine) 
    : currentState(nullptr), transactionData(nullptr), storageEngine(engine) {}

TransactionManager::~TransactionManager() {
    delete currentState;
    if (transactionData) {
        delete transactionData;
    }
}

void TransactionManager::setState(TransactionState* state) {
    if (currentState) {
        delete currentState;  // Clean up previous state
    }
    currentState = state;  // Set the new state
}

void TransactionManager::handleTransaction() {
    if (currentState) {
        currentState->handle(this);  // Delegate to the current state
    } else {
        std::cerr << "No transaction state set!" << std::endl;
    }
}

void TransactionManager::setTransactionData(TransactionData* data) {
    if (transactionData) {
        delete transactionData;
    }
    transactionData = data;  // Set the transaction data
}

TransactionData* TransactionManager::getTransactionData() {
    return transactionData;
}

StorageEngine* TransactionManager::getStorageEngine() {
    return storageEngine;
}

// ActiveState Implementation
void ActiveState::handle(TransactionManager* manager) {
    std::cout << "Transaction is active. Locking resources and tracking changes..." << std::endl;

    // Lock resources
    lockResources(manager);

    // Track changes during the active transaction
    trackChanges(manager);

    // Transition to CommittedState after success
    manager->setState(new CommittedState());
}

void ActiveState::lockResources(TransactionManager* manager) {
    std::cout << "Locking resources for transaction..." << std::endl;
}

void ActiveState::trackChanges(TransactionManager* manager) {
    std::cout << "Tracking changes..." << std::endl;

    // Create new TransactionData and add changes
    manager->setTransactionData(new TransactionData());
    manager->getTransactionData()->addChange("INSERT INTO users VALUES (3, 'Charlie', 22);");
}

// CommittedState Implementation
void CommittedState::handle(TransactionManager* manager) {
    std::cout << "Transaction has been committed. Applying changes..." << std::endl;

    // Apply changes (write to the database)
    applyChanges(manager);

    // Release locks after committing
    releaseLocks(manager);
}

void CommittedState::applyChanges(TransactionManager* manager) {
    TransactionData* data = manager->getTransactionData();
    if (data) {
        std::cout << "Applying changes to the database..." << std::endl;
        for (const auto& change : data->changes) {
            std::cout << "Executing: " << change << std::endl;
            manager->getStorageEngine()->storeData(change);  // Store the changes
        }
    }
}

void CommittedState::releaseLocks(TransactionManager* manager) {
    std::cout << "Releasing locks after commit." << std::endl;
}

// AbortedState Implementation
void AbortedState::handle(TransactionManager* manager) {
    std::cout << "Transaction has been aborted. Rolling back changes..." << std::endl;

    // Rollback changes
    rollbackChanges(manager);

    // Release locks after aborting
    releaseLocks(manager);
}

void AbortedState::rollbackChanges(TransactionManager* manager) {
    std::cout << "Rolling back changes..." << std::endl;
    // Code to undo any changes made during the transaction
}

void AbortedState::releaseLocks(TransactionManager* manager) {
    std::cout << "Releasing locks after abort." << std::endl;
}
