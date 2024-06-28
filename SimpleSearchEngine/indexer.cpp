#include "indexer.h"
#include "tokenizer.h"
#include <fstream>
#include <iostream>

void indexDocument(const std::string& doc, int docId, 
                   std::unordered_map<std::string, std::unordered_set<int>>& index) {
    std::ifstream file(doc);
    if (!file.is_open()) {
        std::cerr << "Could not open the file " << doc << std::endl;
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        auto words = tokenize(line);
        for (const auto& word : words) {
            index[word].insert(docId);
        }
    }
}

void createIndex(const std::vector<std::string>& docs, 
                 std::unordered_map<std::string, std::unordered_set<int>>& index) {
    for (int i = 0; i < docs.size(); ++i) {
        indexDocument(docs[i], i, index);
    }
}

std::unordered_set<int> search(const std::string& query, 
                               const std::unordered_map<std::string, std::unordered_set<int>>& index) {
    auto words = tokenize(query);
    std::unordered_set<int> results;
    for (const auto& word : words) {
        auto it = index.find(word);
        if (it != index.end()) {
            if (results.empty()) {
                results = it->second;
            } else {
                std::unordered_set<int> intersection;
                for (const auto& docId : results) {
                    if (it->second.find(docId) != it->second.end()) {
                        intersection.insert(docId);
                    }
                }
                results = intersection;
            }
        } else {
            results.clear();
            break;
        }
    }
    return results;
}
