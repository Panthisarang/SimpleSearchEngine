cmake_minimum_required(VERSION 3.12)
project(SearchEngine)

set(CMAKE_CXX_STANDARD 14)

# Add pybind11
add_subdirectory(pybind11)

# Create the Python module
pybind11_add_module(search_engine MODULE indexer.cpp tokenizer.cpp)
