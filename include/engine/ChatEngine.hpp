#pragma once
#include "core/LlamaModel.hpp"
#include "core/LlamaContext.hpp"
#include "formatters/IChatFormatter.hpp"
#include "loaders/IPromptLoader.hpp"
#include "samplers/ISampler.hpp"
#include <iostream>
#include <string>
#include <stdexcept>

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
               int max_tokens_per_turn = 2048)
        : model_(model), context_(context), formatter_(formatter),
          sampler_(sampler), max_tokens_per_turn_(max_tokens_per_turn) {}

    void initialize_system_prompt(const IPromptLoader& loader) {
        std::string raw_prompt = loader.load();
        std::cout << "[System Prompt Loaded (" << raw_prompt.length() << " chars)]\n";

        std::string formatted = formatter_.format_system(raw_prompt);
        auto tokens = model_.tokenize(formatted, true);

        if (!context_.decode(tokens)) {
            throw std::runtime_error("Failed to decode system prompt into KV cache!");
        }
    }

    void handle_turn(const std::string& user_message) {
        std::string formatted = formatter_.format_user(user_message);
        auto tokens = model_.tokenize(formatted, false);

        if (!context_.decode(tokens)) {
            std::cerr << "\n[Error: Failed to decode user turn - context limit may be reached]\n";
            return;
        }

        // Print initial brace matching prefilled prompt
        std::cout << "Qwen: {";
        int brace_depth = 1;
        bool in_string = false;
        bool escaped = false;

        for (int i = 0; i < max_tokens_per_turn_; ++i) {
            llama_token id = sampler_.sample(context_);

            if (model_.is_eog(id)) {
                context_.decode(id); // Append EOG token to context
                break;
            }

            std::string piece = model_.token_to_piece(id);
            std::cout << piece << std::flush;

            // Track JSON braces ONLY outside of string literals (ignores braces inside commands like awk '{...}')
            for (char c : piece) {
                if (escaped) {
                    escaped = false;
                    continue;
                }
                if (c == '\\') {
                    escaped = true;
                    continue;
                }
                if (c == '"') {
                    in_string = !in_string;
                } else if (!in_string) {
                    if (c == '{') {
                        brace_depth++;
                    } else if (c == '}') {
                        brace_depth--;
                    }
                }
            }

            if (!context_.decode(id)) {
                break;
            }

            // Clean exit as soon as root JSON object is closed (only outside strings)
            if (!in_string && brace_depth <= 0) {
                break;
            }
        }
        std::cout << "\n";
    }
};
