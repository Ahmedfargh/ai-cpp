#pragma once
#include "IChatFormatter.hpp"

class QwenChatMLFormatter : public IChatFormatter {
public:
    std::string format_system(const std::string& system_text) const override;
    std::string format_user(const std::string& user_text) const override;
};
