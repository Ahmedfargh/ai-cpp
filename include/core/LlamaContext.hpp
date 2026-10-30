#pragma once
#include "llama.h"
#include "LlamaModel.hpp"
#include <vector>
#include <cstdint>
#include <stdexcept>

// RAII Context Holder & KV-cache decoder
class LlamaContext {
private:
    llama_context* ctx_ = nullptr;

public:
    LlamaContext(const LlamaModel& model, uint32_t n_ctx, int n_threads) {
        llama_context_params cparams = llama_context_default_params();
        cparams.n_ctx = n_ctx;
        cparams.n_threads = n_threads;

        ctx_ = llama_init_from_model(model.get(), cparams);
        if (!ctx_) {
            throw std::runtime_error("Failed to create llama context!");
        }
    }

    ~LlamaContext() {
        if (ctx_) {
            llama_free(ctx_);
        }
    }

    LlamaContext(const LlamaContext&) = delete;
    LlamaContext& operator=(const LlamaContext&) = delete;

    llama_context* get() const { return ctx_; }

    bool decode(const std::vector<llama_token>& tokens) {
        if (tokens.empty()) return true;
        llama_batch batch = llama_batch_get_one(const_cast<llama_token*>(tokens.data()), tokens.size());
        return llama_decode(ctx_, batch) == 0;
    }

    bool decode(llama_token token) {
        llama_batch batch = llama_batch_get_one(&token, 1);
        return llama_decode(ctx_, batch) == 0;
    }
};
