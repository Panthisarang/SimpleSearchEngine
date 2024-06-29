#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
#include <unordered_set>

std::string toLower(const std::string& str);
std::vector<std::string> tokenize(const std::string& text);
std::string stem(const std::string& word);
std::vector<std::string> removeStopWords(const std::vector<std::string>& words);

#endif // TOKENIZER_H
