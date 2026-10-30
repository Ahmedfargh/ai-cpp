#include "ggml.h"
#include "gguf.h"
#include <iostream>
#include <vector>

int main() {
    // 1. Initialize ggml context
    struct ggml_init_params params = {
        .mem_size   = 1024 * 1024 * 1024, // 1GB
        .mem_buffer = NULL,
        .no_alloc   = false,
    };
    struct ggml_context * ctx = ggml_init(params);

    // 2. Load the GGUF file
    struct gguf_init_params gguf_params = {
        .no_alloc = false,
        .ctx      = &ctx,
    };
    
    // Your exact file path from the screenshot
    const char * fname = "/home/ahmed/qwen2.5-1.5b-instruct-q5_k_m.gguf";
    struct gguf_context * gguf_ctx = gguf_init_from_file(fname, gguf_params);

    if (!gguf_ctx) {
        std::cerr << "Failed to load GGUF file!" << std::endl;
        return 1;
    }

    std::cout << "Loaded GGUF. Tensors: " << gguf_get_n_tensors(gguf_ctx) << "\n";

    // 3. Get Metadata (Qwen2 specific)
    int key_idx = gguf_find_key(gguf_ctx, "qwen2.block_count");
    if (key_idx != -1) {
        uint32_t n_layers = gguf_get_val_u32(gguf_ctx, key_idx);
        std::cout << "Qwen2 Layers: " << n_layers << "\n";
    }

    // --- YOUR WORK STARTS HERE ---
    // You now have to build the graph:
    // 1. Tokenize the prompt (You need to implement a BPE tokenizer or use HF tokenizers)
    // 2. ggml_get_tensor(ctx, "token_embd.weight") to get embeddings
    // 3. Loop through layers:
    //    - ggml_rms_norm()
    //    - ggml_mul_mat() using the Q5_K weights
    //    - ggml_rope()
    //    - ggml_soft_max()
    //    - ggml_silu()
    // 4. Sample the next token.
    
    gguf_free(gguf_ctx);
    ggml_free(ctx);
    return 0;
}