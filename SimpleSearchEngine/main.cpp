#include <iostream>
#include <vector>
#include <unordered_map>
#include "indexer.h"

int main() {
    // List of documents (plain text files)
    std::vector<std::string> documents = {"doc1.txt", "doc2.txt", "doc3.txt"};

    // Create an inverted index
    std::unordered_map<std::string, std::vector<Posting>> index;
    createIndex(documents, index);

    // Query the index
    std::string query;
    std::cout << "Enter a query: ";
    std::getline(std::cin, query);

    auto results = search(query, index, documents);
    if (results.empty()) {
        std::cout << "No documents found." << std::endl;
    } else {
        std::cout << "Documents found: ";
        for (const auto& docId : results) {
            std::cout << "doc" << (docId + 1) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
