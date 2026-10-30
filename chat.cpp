#include "llama.h"
#include "loaders/FilePromptLoader.hpp"
#include "loaders/SystemAwarePromptLoader.hpp"
#include "formatters/QwenChatMLFormatter.hpp"
#include "core/LlamaModel.hpp"
#include "core/LlamaContext.hpp"
#include "samplers/ConfigurableSampler.hpp"
#include "engine/ChatEngine.hpp"
#include <iostream>
#include <string>
#include <memory>

int main() {
    llama_log_set([](ggml_log_level level, const char* text, void*) {
        if (level >= GGML_LOG_LEVEL_ERROR) std::cerr << text;
    }, nullptr);

    llama_backend_init();

    try {
        // App Configuration
        const std::string model_path = "./models/commanders/josiefied-qwen2.5-1.5b-instruct-abliterated-v1.IQ4_XS.gguf";
        const std::string prompt_file = "system_prompt.txt";
        const uint32_t context_size = 4096;
        const int threads = 6;

        // Composition Root: Instantiate dependencies
        LlamaModel model(model_path, 0);
        LlamaContext context(model, context_size, threads);
        QwenChatMLFormatter formatter;

        // Sampler with gentle repetition penalty (1.03) and focused temp (0.3) for clean multi-step JSON
        int n_vocab = llama_vocab_n_tokens(model.vocab());
        ConfigurableSampler sampler(n_vocab, 0.3f, 0.95f, 1.03f);

        // Decorate file loader with live host OS & device telemetry
        auto base_file_loader = std::make_unique<FilePromptLoader>(prompt_file);
        SystemAwarePromptLoader prompt_loader(std::move(base_file_loader));

        // Inject dependencies into the engine (with max 3072 tokens and JSON auto-closing)
        ChatEngine engine(model, context, formatter, sampler, 3072);
        engine.initialize_system_prompt(prompt_loader);

        std::cout << "\nChat session ready. Type your message (or 'exit' to quit):\n";

        // Interactive terminal loop
        while (true) {
            std::cout << "\nYou: ";
            std::string input;
            if (!std::getline(std::cin, input) || input == "exit") {
                break;
            }
            if (input.empty()) continue;

            engine.handle_turn(input);
        }

    } catch (const std::exception& ex) {
        std::cerr << "Fatal Error: " << ex.what() << "\n";
        llama_backend_free();
        return 1;
    }

    llama_backend_free();
    return 0;
}
