// InvertedIndex.h

#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include <vector>
#include <string>
#include <unordered_map>

struct Entry {
    size_t doc_id;
    size_t count;
    bool operator ==(const Entry& other) const;
};

class InvertedIndex {
public:
    void UpdateDocumentBase(std::vector<std::string>& input_docs);
    std::vector<Entry> GetWordCount(const std::string& word);

private:
    std::unordered_map<std::string, std::vector<Entry>> freq_dictionary;
    std::vector<std::string> docs;
};

#endif // INVERTED_INDEX_H

