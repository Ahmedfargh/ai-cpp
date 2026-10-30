#pragma once
#include <string>

class IChatFormatter {
public:
    virtual ~IChatFormatter() = default;
    virtual std::string format_system(const std::string& system_text) const = 0;
    virtual std::string format_user(const std::string& user_text) const = 0;
};
