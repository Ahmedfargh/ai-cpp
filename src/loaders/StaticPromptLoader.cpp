#include "loaders/StaticPromptLoader.hpp"
#include <utility>

StaticPromptLoader::StaticPromptLoader(std::string prompt) : prompt_(std::move(prompt)) {}

std::string StaticPromptLoader::load() const {
    return prompt_;
}
