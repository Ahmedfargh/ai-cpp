#pragma once
#include "llama.h"
#include <string>
#include <vector>

// RAII Model Loader & Vocabulary Manager
class LlamaModel {
private:
    llama_model* model_ = nullptr;
    const llama_vocab* vocab_ = nullptr;

public:
    explicit LlamaModel(const std::string& model_path, int n_gpu_layers = 0);
    ~LlamaModel();

    LlamaModel(const LlamaModel&) = delete;
    LlamaModel& operator=(const LlamaModel&) = delete;

    llama_model* get() const { return model_; }
    const llama_vocab* vocab() const { return vocab_; }

    std::vector<llama_token> tokenize(const std::string& text, bool add_special) const;
    std::string token_to_piece(llama_token id) const;
    bool is_eog(llama_token id) const;
};
