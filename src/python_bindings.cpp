#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "TransactionManager.hpp"
#include "StorageEngine.hpp"
#include "DatabaseEngine.hpp"

namespace py = pybind11;

PYBIND11_MODULE(database_engine, m) {
    m.doc() = "Python bindings for the C++ Database Engine";

    // Bind DatabaseEngine
    py::class_<DatabaseEngine>(m, "DatabaseEngine")
        .def(py::init<>())  // Expose the default constructor
        .def("initializeDatabase", &DatabaseEngine::initializeDatabase)
        .def("createTable", &DatabaseEngine::createTable)
        .def("insertData", &DatabaseEngine::insertData)
        .def("executeQuery", &DatabaseEngine::executeQuery)
        .def("startTransaction", &DatabaseEngine::startTransaction)
        .def("commitTransaction", &DatabaseEngine::commitTransaction)
        .def("rollbackTransaction", &DatabaseEngine::rollbackTransaction)
        .def("setStorageEngine", &DatabaseEngine::setStorageEngine);

    // Bind StorageEngine
    py::class_<StorageEngine>(m, "StorageEngine")
        .def(py::init<const std::string&>())
        .def("storeData", &StorageEngine::storeData)
        .def("retrieveData", &StorageEngine::retrieveData);

    // Bind TransactionManager
    py::class_<TransactionManager>(m, "TransactionManager")
        .def(py::init<StorageEngine*>())
        .def("setState", &TransactionManager::setState)
        .def("handleTransaction", &TransactionManager::handleTransaction)
        .def("setTransactionData", &TransactionManager::setTransactionData)
        .def("getTransactionData", &TransactionManager::getTransactionData)
        .def("getStorageEngine", &TransactionManager::getStorageEngine);

    // Bind TransactionState classes (ActiveState, CommittedState, AbortedState)
    py::class_<ActiveState, TransactionState>(m, "ActiveState")
        .def(py::init<>())
        .def("handle", &ActiveState::handle);

    py::class_<CommittedState, TransactionState>(m, "CommittedState")
        .def(py::init<>())
        .def("handle", &CommittedState::handle);

    py::class_<AbortedState, TransactionState>(m, "AbortedState")
        .def(py::init<>())
        .def("handle", &AbortedState::handle);
}
