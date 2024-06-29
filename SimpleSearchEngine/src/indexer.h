#ifndef INDEXER_H
#define INDEXER_H

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <mutex>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

struct Posting {
    int docId;
    std::vector<int> positions;
};

void indexDocument(const std::string& doc, int docId, 
                   std::unordered_map<std::string, std::vector<Posting>>& index,
                   std::mutex& indexMutex);
void createIndex(const std::vector<std::string>& docs, 
                 std::unordered_map<std::string, std::vector<Posting>>& index);
std::vector<int> search(const std::string& query, 
                        const std::unordered_map<std::string, std::vector<Posting>>& index, 
                        const std::vector<std::string>& docs);

PYBIND11_MODULE(search_engine, m) {
    m.def("createIndex", &createIndex);
    m.def("search", &search);
}

#endif // INDEXER_H