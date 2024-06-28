#ifndef INDEXER_H
#define INDEXER_H

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>

void indexDocument(const std::string& doc, int docId, 
                   std::unordered_map<std::string, std::unordered_set<int>>& index);
void createIndex(const std::vector<std::string>& docs, 
                 std::unordered_map<std::string, std::unordered_set<int>>& index);
std::unordered_set<int> search(const std::string& query, 
                               const std::unordered_map<std::string, std::unordered_set<int>>& index);

#endif // INDEXER_H
