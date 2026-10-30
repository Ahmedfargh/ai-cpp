#include "samplers/ConfigurableSampler.hpp"

ConfigurableSampler::ConfigurableSampler(int n_vocab, float temp, float top_p, float repeat_penalty, float penalty_freq, float penalty_present) {
    llama_sampler_chain_params sparams = llama_sampler_chain_default_params();
    smpl_ = llama_sampler_chain_init(sparams);

    // 1. Repetition penalties (low penalty so identical JSON schema keys across steps are not penalized)
    llama_sampler_chain_add(smpl_, llama_sampler_init_penalties(
        n_vocab,
        64,               // check last 64 tokens
        repeat_penalty,   // slight penalty to avoid loops, but keep schema keys accessible
        penalty_freq,     // frequency penalty
        penalty_present   // presence penalty
    ));

    // 2. Top-K and Top-P filtering
    llama_sampler_chain_add(smpl_, llama_sampler_init_top_k(40));
    llama_sampler_chain_add(smpl_, llama_sampler_init_top_p(top_p, 1));

    // 3. Temperature
    llama_sampler_chain_add(smpl_, llama_sampler_init_temp(temp));

    // 4. Distribution sampler for final token selection
    llama_sampler_chain_add(smpl_, llama_sampler_init_dist(LLAMA_DEFAULT_SEED));
}

ConfigurableSampler::~ConfigurableSampler() {
    if (smpl_) {
        llama_sampler_free(smpl_);
    }
}

llama_token ConfigurableSampler::sample(LlamaContext& ctx) {
    return llama_sampler_sample(smpl_, ctx.get(), -1);
}
