// ConverterJSON.cpp

#include "ConverterJSON.h"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

static json ReadJSONFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file " + filename);
    }
    json fileJSON;
    file >> fileJSON;
    file.close();
    return fileJSON;
}

std::vector<std::string> ConverterJSON::GetTextDocuments() {
    std::vector<std::string> configFilesContent;
    json fileJSON = ReadJSONFromFile("config.json");

    for (const auto& i : fileJSON["files"]) {
        std::ifstream file(i.get<std::string>());
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file " + i.get<std::string>());
        }
        std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        configFilesContent.push_back(fileContent);
        file.close();
    }
    return configFilesContent;
}

int ConverterJSON::GetResponsesLimit() {
    json fileJSON = ReadJSONFromFile("config.json");
    int ResponsesLimit = fileJSON["config"]["max_responses"].get<int>();
    return ResponsesLimit;
}

std::vector<std::string> ConverterJSON::GetRequests() {
    std::vector<std::string> Requests;
    json fileJSON = ReadJSONFromFile("requests.json");

    for (const auto& i : fileJSON["requests"]) {
        Requests.push_back(i.get<std::string>());
    }
    return Requests;
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers) {
    std::vector<std::string> Requests = GetRequests();
    std::vector<std::string> IDs = GenerateIDs(Requests);

    json answersJSON;

    for (size_t i = 0; i < answers.size(); ++i) {
        if (answers[i].empty()) {
            answersJSON["answers"][IDs[i]]["result"] = false;
        } else if (answers[i].size() == 1) {
            answersJSON["answers"][IDs[i]]["result"] = true;
            answersJSON["answers"][IDs[i]]["docid"] = answers[i][0].first;
            answersJSON["answers"][IDs[i]]["rank"] = answers[i][0].second;
        } else {
            answersJSON["answers"][IDs[i]]["result"] = true;
            answersJSON["answers"][IDs[i]]["relevance"] = json::array();
            for (const auto& answer : answers[i]) {
                json docInfo;
                docInfo["docid"] = answer.first;
                docInfo["rank"] = answer.second;
                answersJSON["answers"][IDs[i]]["relevance"].push_back(docInfo);
            }
        }
    }

    std::ofstream outFile("answers.json");
    if (!outFile.is_open()) {
        throw std::runtime_error("Cannot open file answers.json for writing");
    }
    outFile << answersJSON.dump(4);
    outFile.close();
}

std::vector<std::string> ConverterJSON::GenerateIDs(const std::vector<std::string>& Requests) {
    std::vector<std::string> IDs;
    for (size_t i = 1; i <= Requests.size(); ++i) {
        int iLng = NumOfDigits(static_cast<int>(i));
        IDs.push_back("request" + StringMultiply("0", 3 - iLng) + std::to_string(i));
    }
    return IDs;
}

int ConverterJSON::NumOfDigits(int n) {
    int c = 0;
    do {
        c++;
        n /= 10;
    } while(n);
    return c;
}

std::string ConverterJSON::StringMultiply(const std::string &str, int n) {
    std::string result;
    for (int i = 0; i < n; ++i) {
        result += str;
    }
    return result;
}
