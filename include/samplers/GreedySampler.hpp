#pragma once
#include "ISampler.hpp"

class GreedySampler : public ISampler {
private:
    llama_sampler* smpl_ = nullptr;

public:
    GreedySampler() {
        smpl_ = llama_sampler_init_greedy();
    }

    ~GreedySampler() override {
        if (smpl_) llama_sampler_free(smpl_);
    }

    GreedySampler(const GreedySampler&) = delete;
    GreedySampler& operator=(const GreedySampler&) = delete;

    llama_token sample(LlamaContext& ctx) override {
        return llama_sampler_sample(smpl_, ctx.get(), -1);
    }
};
