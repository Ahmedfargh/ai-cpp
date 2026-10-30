#pragma once
#include <string>
#include <cstdint>

enum class OSFamily {
    WINDOWS,
    UNIX_LINUX,
    UNIX_MACOS,
    UNKNOWN
};

struct PlatformInfo {
    OSFamily family;
    std::string os_family_str;
    std::string os_name;
    std::string kernel_version;
    std::string architecture;
    int cpu_threads = 1;
    uint64_t total_ram_mb = 0;
    uint64_t free_ram_mb = 0;
    std::string default_shell;
    std::string suggested_pkg_manager;
    std::string compiler_toolchain;
};

class PlatformDetector {
public:
    static PlatformInfo detect();
};
