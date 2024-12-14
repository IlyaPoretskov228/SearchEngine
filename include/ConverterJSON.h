// ConverterJSON.h

#ifndef CONVERTER_JSON_H
#define CONVERTER_JSON_H

#pragma once
#include <vector>
#include <string>
#include <nlohmann/json.hpp>

class ConverterJSON {
public:
    std::vector<std::string> GetTextDocuments();
    int GetResponsesLimit();
    std::vector<std::string> GetRequests();
    void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);

private:
    std::vector<std::string> GenerateIDs(const std::vector<std::string>& Requests);
    int NumOfDigits(int n);
    std::string StringMultiply(const std::string &str, int n);
};

#endif // CONVERTER_JSON_H
