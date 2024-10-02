// SearchServer.h

#ifndef SEARCH_SERVER_H
#define SEARCH_SERVER_H

#include "InvertedIndex.h"
#include <vector>
#include <string>

struct RelativeIndex {
    size_t doc_id;
    float rank;
};

class SearchServer {
public:
    SearchServer(InvertedIndex& idx) : _index(idx) { }
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string> &queries_input);

private:
    InvertedIndex& _index;
};

#endif // SEARCH_SERVER_H
