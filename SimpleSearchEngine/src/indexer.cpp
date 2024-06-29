#include "indexer.h"
#include "tokenizer.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <map>

void indexDocument(const std::string& doc, int docId, 
                   std::unordered_map<std::string, std::vector<Posting>>& index) {
    std::ifstream file(doc);
    if (!file.is_open()) {
        std::cerr << "Could not open the file " << doc << std::endl;
        return;
    }

    std::string line;
    int position = 0;
    while (std::getline(file, line)) {
        auto words = tokenize(line);
        words = removeStopWords(words);
        for (const auto& word : words) {
            std::string stemmedWord = stem(word);
            index[stemmedWord].push_back({docId, {position}});
            position++;
        }
    }
}

void createIndex(const std::vector<std::string>& docs, 
                 std::unordered_map<std::string, std::vector<Posting>>& index) {
    for (int i = 0; i < docs.size(); ++i) {
        indexDocument(docs[i], i, index);
    }
}

std::vector<int> search(const std::string& query, 
                        const std::unordered_map<std::string, std::vector<Posting>>& index, 
                        const std::vector<std::string>& docs) {
    auto words = tokenize(query);
    words = removeStopWords(words);
    if (words.empty()) return {};

    std::unordered_map<int, double> docScores;
    int totalDocs = docs.size();

    for (const auto& word : words) {
        std::string stemmedWord = stem(word);
        auto it = index.find(stemmedWord);
        if (it != index.end()) {
            int docFreq = it->second.size();
            double idf = log(static_cast<double>(totalDocs) / (1 + docFreq));
            for (const auto& posting : it->second) {
                int termFreq = posting.positions.size();
                double tf = 1 + log(termFreq);
                docScores[posting.docId] += tf * idf;
            }
        }
    }

    // Sort documents by score
    std::vector<std::pair<int, double>> sortedDocs(docScores.begin(), docScores.end());
    std::sort(sortedDocs.begin(), sortedDocs.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    // Collect results
    std::vector<int> results;
    for (const auto& doc : sortedDocs) {
        results.push_back(doc.first);
    }

    return results;
}
