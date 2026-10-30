#pragma once
#include "ISampler.hpp"
#include "llama.h"

class ConfigurableSampler : public ISampler {
private:
    llama_sampler* smpl_ = nullptr;

public:
    ConfigurableSampler(int n_vocab, float temp = 0.3f, float top_p = 0.95f, float repeat_penalty = 1.03f, float penalty_freq = 0.0f, float penalty_present = 0.0f);
    ~ConfigurableSampler() override;

    ConfigurableSampler(const ConfigurableSampler&) = delete;
    ConfigurableSampler& operator=(const ConfigurableSampler&) = delete;

    llama_token sample(LlamaContext& ctx) override;
};
