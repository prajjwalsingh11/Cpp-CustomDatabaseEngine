// TransactionManager.h
//state pattern

#pragma once
#include <string>
#include <iostream>
using namespace std;

class TransactionState {
public:
    virtual void handle() = 0;
    virtual ~TransactionState() = default;
};

class ActiveState : public TransactionState {
public:
    void handle() override {
        cout << "Transaction is Active" << endl;
    }
};

class CommittedState : public TransactionState {
public:
    void handle() override {
        cout << "Transaction is Committed" << endl;
    }
};

class RolledBackState : public TransactionState {
public:
    void handle() override {
        cout << "Transaction is Rolled Back" << endl;
    }
};

class TransactionManager {
public:
    void setState(TransactionState* state) {
        currentState = state;
    }

    void handleTransaction() {
        currentState->handle();
    }

private:
    TransactionState* currentState;
};
