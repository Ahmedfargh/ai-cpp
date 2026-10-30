#pragma once
#include "IPromptLoader.hpp"
#include <utility>

class StaticPromptLoader : public IPromptLoader {
private:
    std::string prompt_;

public:
    explicit StaticPromptLoader(std::string prompt) : prompt_(std::move(prompt)) {}

    std::string load() const override {
        return prompt_;
    }
};
