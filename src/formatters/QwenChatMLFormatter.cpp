#include "formatters/QwenChatMLFormatter.hpp"

std::string QwenChatMLFormatter::format_system(const std::string& system_text) const {
    return "<|im_start|>system\n" + system_text + "<|im_end|>\n";
}

std::string QwenChatMLFormatter::format_user(const std::string& user_text) const {
    // Prefill assistant response with '{' to force pure JSON output immediately
    return "<|im_start|>user\n" + user_text + "<|im_end|>\n<|im_start|>assistant\n{";
}
