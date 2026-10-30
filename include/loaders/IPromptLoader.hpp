#pragma once
#include <string>

// Interface for loading prompts (Open for extension, closed for modification)
class IPromptLoader {
public:
    virtual ~IPromptLoader() = default;
    virtual std::string load() const = 0;
};
