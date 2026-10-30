#include "loaders/FilePromptLoader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>

FilePromptLoader::FilePromptLoader(std::string filepath, std::string fallback)
    : filepath_(std::move(filepath)), fallback_(std::move(fallback)) {}

std::string FilePromptLoader::load() const {
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
