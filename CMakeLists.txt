# Specify the minimum CMake version
cmake_minimum_required(VERSION 3.31.0)

# Set the project name
project(CustomDatabaseEngine)

# Ensure proper C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Python interpreter and development libraries
find_package(Python 3.13 REQUIRED COMPONENTS Interpreter Development Development.Module)

# Include Python headers and libraries
include_directories(${Python_INCLUDE_DIRS})
# Link & include the SQLite3 library & headers (update with your actual path)
link_directories("C:/coding/CustomDatabaseEngine/sqlite3/lib")
include_directories("C:/coding/CustomDatabaseEngine/sqlite3/lib")

# Include Pybind11 as a submodule
add_subdirectory(pybind11)

# Add the core database engine source files
set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/DatabaseEngine.cpp
    ${CMAKE_SOURCE_DIR}/src/StorageEngine.cpp
    ${CMAKE_SOURCE_DIR}/src/QueryProcessor.cpp
    ${CMAKE_SOURCE_DIR}/src/TransactionManager.cpp
    ${CMAKE_SOURCE_DIR}/src/Indexing.cpp
)

# Add the headers
set(HEADERS
    ${CMAKE_SOURCE_DIR}/src/DatabaseEngine.hpp
    ${CMAKE_SOURCE_DIR}/src/StorageEngine.hpp
    ${CMAKE_SOURCE_DIR}/src/QueryProcessor.hpp
    ${CMAKE_SOURCE_DIR}/src/TransactionManager.hpp
    ${CMAKE_SOURCE_DIR}/src/Indexing.hpp
)

# Create the main library target
add_library(CustomDatabaseEngine STATIC ${SOURCES} ${HEADERS})

# Create the Pybind11 module
pybind11_add_module(database_engine ${CMAKE_SOURCE_DIR}/src/python_bindings.cpp)

# Link the core library with the Python module
target_link_libraries(database_engine PRIVATE CustomDatabaseEngine ${Python_LIBRARIES})

# Link SQLite3 with your project
target_link_libraries(CustomDatabaseEngine sqlite3)

# Ensure the sqlite3.dll is copied alongside your executable if using dynamic linking
# You can copy sqlite3.dll manually or use a CMake command to copy it
add_custom_command(TARGET CustomDatabaseEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/coding/CustomDatabaseEngine/sqlite3/lib/sqlite3.dll"
        $<TARGET_FILE_DIR:CustomDatabaseEngine>)