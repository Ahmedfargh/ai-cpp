#pragma once
#include "IPromptLoader.hpp"
#include <string>

class StaticPromptLoader : public IPromptLoader {
private:
    std::string prompt_;

public:
    explicit StaticPromptLoader(std::string prompt);
    std::string load() const override;
};
