#include "QueryProcessor.h"
#include <iostream>

void testQueryProcessor() {
    QueryProcessor processor;

    // Add query components
    processor.addComponent(std::make_shared<SelectQuery>());
    processor.addComponent(std::make_shared<WhereClause>());
    processor.addComponent(std::make_shared<JoinQuery>());

    // Execute query (should print all query components)
    processor.executeQuery();
}

int main() {
    testQueryProcessor();
    return 0;
}
