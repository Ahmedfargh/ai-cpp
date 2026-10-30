#pragma once
#include "llama.h"
#include "LlamaModel.hpp"
#include <vector>
#include <cstdint>

// RAII Context Holder & KV-cache decoder
class LlamaContext {
private:
    llama_context* ctx_ = nullptr;

public:
    LlamaContext(const LlamaModel& model, uint32_t n_ctx, int n_threads);
    ~LlamaContext();

    LlamaContext(const LlamaContext&) = delete;
    LlamaContext& operator=(const LlamaContext&) = delete;

    llama_context* get() const { return ctx_; }

    bool decode(const std::vector<llama_token>& tokens);
    bool decode(llama_token token);
};
