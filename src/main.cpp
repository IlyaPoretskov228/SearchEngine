#include <iostream>
#include <string>
#include <fstream>
#include "ConverterJSON.h"
#include "SearchServer.h"
#include "InvertedIndex.h"
#include <nlohmann/json.hpp>

int main() {
    try {
        ConverterJSON converter;

        std::vector<std::string> documents = converter.GetTextDocuments();

        InvertedIndex index;
        index.UpdateDocumentBase(documents);

        SearchServer searchServer(index);

        std::vector<std::string> requests = converter.GetRequests();

        std::vector<std::vector<RelativeIndex>> searchResults = searchServer.search(requests);

        std::vector<std::vector<std::pair<int, float>>> convertedResults;

        for (const auto& resultSet : searchResults) {
            std::vector<std::pair<int, float>> convertedSet;
            for (const auto& result : resultSet) {
                convertedSet.emplace_back(static_cast<int>(result.doc_id), result.rank);
            }
            convertedResults.push_back(convertedSet);
        }

        converter.putAnswers(convertedResults);

        std::cout << "Search queries processed and results saved to answers.json" << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
