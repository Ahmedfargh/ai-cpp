#pragma once
#include "llama.h"
#include "core/LlamaContext.hpp"

// Sampler abstraction (Open/Closed principle)
class ISampler {
public:
    virtual ~ISampler() = default;
    virtual llama_token sample(LlamaContext& ctx) = 0;
};
