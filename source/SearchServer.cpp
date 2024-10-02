// SearchServer.cpp

#include "SearchServer.h"
#include <algorithm>
#include <unordered_map>
#include <sstream>

// Template function to remove duplicates
template<typename T>
void unique_elements(std::vector<T>& vec) {
    std::sort(vec.begin(), vec.end());
    auto last = std::unique(vec.begin(), vec.end());
    vec.erase(last, vec.end());
}

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input) {
    std::vector<std::vector<RelativeIndex>> searchResults;

    for (const std::string& query : queries_input) {
        std::vector<std::string> reqWords;
        std::stringstream docStream(query);

        for (std::string word; docStream >> word; ) {
            reqWords.push_back(word);
        }

        unique_elements(reqWords);

        std::unordered_map<size_t, float> docRelevance;

        for (const std::string& word : reqWords) {
            std::vector<Entry> wordEntries = _index.GetWordCount(word);

            for (const Entry& entry : wordEntries) {
                docRelevance[entry.doc_id] += entry.count;
            }
        }

        std::vector<RelativeIndex> relativeIndices;

        float maxRelevance = 0;
        for (const auto& [doc_id, relevance] : docRelevance) {
            if (relevance > maxRelevance) {
                maxRelevance = relevance;
            }
        }

        for (const auto& [doc_id, relevance] : docRelevance) {
            relativeIndices.push_back({doc_id, relevance / maxRelevance});
        }

        std::sort(relativeIndices.begin(), relativeIndices.end(),
                  [](const RelativeIndex& a, const RelativeIndex& b) {
                      return a.rank > b.rank;
                  });

        searchResults.push_back(relativeIndices);
    }

    return searchResults;
}
