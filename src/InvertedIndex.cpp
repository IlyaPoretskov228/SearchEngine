#include <InvertedIndex.h>
#include <set>
#include <sstream>
#include <utility>
#include <thread>
#include <mutex>

std::mutex index_mutex;

bool Entry::operator==(const Entry &other) const {
    return (doc_id == other.doc_id &&
            count == other.count);
}

void CalculateWordCount(InvertedIndex* ii, std::string &Word, std::vector<Entry> &v) {
    v = ii->GetWordCount(Word);
}

void InvertedIndex::UpdateDocumentBase(std::vector<std::string>& input_docs) {
    docs = std::move(input_docs);

    std::vector<std::thread> threads;

    for (size_t i = 0; i < docs.size(); ++i) {
        threads.emplace_back([this, i]() {
            std::unordered_map<std::string, size_t> local_word_count;
            std::stringstream docStream(docs[i]);
            std::string word;

            while (docStream >> word) {
                ++local_word_count[word];
            }

            std::lock_guard<std::mutex> guard(index_mutex);

            for (const auto& [word, count] : local_word_count) {
                freq_dictionary[word].push_back({i, count});
            }
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word) {

    std::vector<Entry> returnedVector;

    for (size_t i = 0; i < docs.size(); ++i) {
        //добавление в вектор содержимое документа и разбиение его на слова
        std::vector<std::string> docWords;
        std::stringstream docStream(docs[i]);

        for (std::string addedString; getline(docStream, addedString, ' ');) {
            docWords.push_back(addedString);
        }

        for (const auto & docWord : docWords) {
            if (docWord == word) {
                /**
                 *булевая переменная указывает на то, было ли найдено ещё одно вхождение слова в тот же файл
                */
                bool hasFound = false;
                int returnedVectorIndex;
                for (int j = 0; j < returnedVector.size(); ++j) {
                    if (returnedVector[j].doc_id == i) {
                        hasFound = true;
                        returnedVectorIndex = j;
                        break;
                    }
                }
                if (hasFound) {
                    returnedVector[returnedVectorIndex].count++;
                } else {
                    returnedVector.push_back({i, 1});
                }
            }
        }
    }
    return returnedVector;
}