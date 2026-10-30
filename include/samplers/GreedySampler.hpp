#pragma once
#include "ISampler.hpp"
#include "llama.h"

class GreedySampler : public ISampler {
private:
    llama_sampler* smpl_ = nullptr;

public:
    GreedySampler();
    ~GreedySampler() override;

    GreedySampler(const GreedySampler&) = delete;
    GreedySampler& operator=(const GreedySampler&) = delete;

    llama_token sample(LlamaContext& ctx) override;
};
