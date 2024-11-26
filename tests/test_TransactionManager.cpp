#include "TransactionManager.h"
#include <iostream>

void testTransactionManager() {
    TransactionManager transactionManager;

    ActiveState activeState;
    transactionManager.setState(&activeState);
    transactionManager.handleTransaction();  // Should print "Transaction is Active"

    CommittedState committedState;
    transactionManager.setState(&committedState);
    transactionManager.handleTransaction();  // Should print "Transaction is Committed"

    RolledBackState rolledBackState;
    transactionManager.setState(&rolledBackState);
    transactionManager.handleTransaction();  // Should print "Transaction is Rolled Back"
}

int main() {
    testTransactionManager();
    return 0;
}
