#pragma once
#include "IPromptLoader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
using std::string;
class FilePromptLoader: public IPromptLoader {
private:
    string filepath_;
    string fallback_;

public:
    FilePromptLoader(string filepath, string fallback = "You are a helpful assistant.")
        : filepath_(std::move(filepath)), fallback_(std::move(fallback)) {}

    std::string load() const override {
        std::ifstream file(filepath_);
        if (!file.is_open()) {
            std::cerr << "[PromptLoader] Warning: Could not open " << filepath_
                      << ", using fallback prompt.\n";
            return fallback_;
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
};
