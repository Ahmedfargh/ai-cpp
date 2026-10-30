#pragma once
#include "IPromptLoader.hpp"
#include <memory>
#include <string>

// Decorator: dynamically detects whether the host is Windows or Unix-based and injects the OS profile
class SystemAwarePromptLoader : public IPromptLoader {
private:
    std::unique_ptr<IPromptLoader> base_loader_;

public:
    explicit SystemAwarePromptLoader(std::unique_ptr<IPromptLoader> base_loader);
    ~SystemAwarePromptLoader() override = default;

    std::string load() const override;
};
