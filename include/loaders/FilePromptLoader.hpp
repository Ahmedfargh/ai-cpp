#pragma once
#include "IPromptLoader.hpp"
#include <string>

class FilePromptLoader : public IPromptLoader {
private:
    std::string filepath_;
    std::string fallback_;

public:
    FilePromptLoader(std::string filepath, std::string fallback = "You are a helpful assistant.");
    std::string load() const override;
};
