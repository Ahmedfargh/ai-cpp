#pragma once
#include "core/LlamaModel.hpp"
#include "core/LlamaContext.hpp"
#include "formatters/IChatFormatter.hpp"
#include "loaders/IPromptLoader.hpp"
#include "samplers/ISampler.hpp"
#include <string>

// Orchestrates chat lifecycle via Dependency Inversion
class ChatEngine {
private:
    const LlamaModel& model_;
    LlamaContext& context_;
    const IChatFormatter& formatter_;
    ISampler& sampler_;
    int max_tokens_per_turn_;

public:
    ChatEngine(const LlamaModel& model,
               LlamaContext& context,
               const IChatFormatter& formatter,
               ISampler& sampler,
               int max_tokens_per_turn = 2048);

    void initialize_system_prompt(const IPromptLoader& loader);
    void handle_turn(const std::string& user_message);
};
