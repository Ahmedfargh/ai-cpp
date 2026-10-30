#pragma once
#include "IChatFormatter.hpp"

class QwenChatMLFormatter : public IChatFormatter {
public:
    std::string format_system(const std::string& system_text) const override {
        return "<|im_start|>system\n" + system_text + "<|im_end|>\n";
    }

    std::string format_user(const std::string& user_text) const override {
        // Prefill assistant response with '{' to force pure JSON output immediately
        return "<|im_start|>user\n" + user_text + "<|im_end|>\n<|im_start|>assistant\n{";
    }
};
