// QueryProcessor.h
//composite pattern

#pragma once
#include <vector>
#include <memory>
#include <iostream>
using namespace std;

class QueryComponent {
public:
    virtual void execute() = 0;
    virtual ~QueryComponent() = default;
};

class SelectQuery : public QueryComponent {
public:
    void execute() override {
        cout << "Executing SELECT query" << endl;
    }
};

class WhereClause : public QueryComponent {
public:
    void execute() override {
        cout << "Executing WHERE clause" << endl;
    }
};

class QueryProcessor {
public:
    void addComponent(shared_ptr<QueryComponent> component) {
        components.push_back(component);
    }

    void executeQuery() {
        for (auto& component : components) {
            component->execute();
        }
    }

private:
    vector<shared_ptr<QueryComponent>> components;
};
