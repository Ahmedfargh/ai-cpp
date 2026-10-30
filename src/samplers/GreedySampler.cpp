#include "samplers/GreedySampler.hpp"

GreedySampler::GreedySampler() {
    smpl_ = llama_sampler_init_greedy();
}

GreedySampler::~GreedySampler() {
    if (smpl_) {
        llama_sampler_free(smpl_);
    }
}

llama_token GreedySampler::sample(LlamaContext& ctx) {
    return llama_sampler_sample(smpl_, ctx.get(), -1);
}
