#include "core/LlamaModel.hpp"
#include <stdexcept>

LlamaModel::LlamaModel(const std::string& model_path, int n_gpu_layers) {
    llama_model_params mparams = llama_model_default_params();
    mparams.n_gpu_layers = n_gpu_layers;

    model_ = llama_model_load_from_file(model_path.c_str(), mparams);
    if (!model_) {
        throw std::runtime_error("Failed to load model from: " + model_path);
    }
    vocab_ = llama_model_get_vocab(model_);
}

LlamaModel::~LlamaModel() {
    if (model_) {
        llama_model_free(model_);
    }
}

std::vector<llama_token> LlamaModel::tokenize(const std::string& text, bool add_special) const {
    int n_tok = -llama_tokenize(vocab_, text.c_str(), text.length(), nullptr, 0, add_special, true);
    std::vector<llama_token> tokens(n_tok);
    llama_tokenize(vocab_, text.c_str(), text.length(), tokens.data(), n_tok, add_special, true);
    return tokens;
}

std::string LlamaModel::token_to_piece(llama_token id) const {
    char buf[128];
    int n = llama_token_to_piece(vocab_, id, buf, sizeof(buf), 0, true);
    if (n > 0) return std::string(buf, n);
    return "";
}

bool LlamaModel::is_eog(llama_token id) const {
    return llama_vocab_is_eog(vocab_, id);
}
