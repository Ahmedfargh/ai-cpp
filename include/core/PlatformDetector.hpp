#pragma once
#include <string>
#include <sstream>
#include <cstdint>

#if defined(_WIN32) || defined(_WIN64)
    #define PLATFORM_WINDOWS 1
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #include <windows.h>
#elif defined(__APPLE__)
    #define PLATFORM_MACOS 1
    #include <sys/utsname.h>
    #include <sys/sysctl.h>
    #include <unistd.h>
#elif defined(__linux__) || defined(__unix__)
    #define PLATFORM_UNIX 1
    #include <sys/utsname.h>
    #include <sys/sysinfo.h>
    #include <unistd.h>
    #include <fstream>
#else
    #define PLATFORM_UNKNOWN 1
#endif

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
    static PlatformInfo detect() {
        PlatformInfo info;

#if defined(PLATFORM_WINDOWS)
        info.family = OSFamily::WINDOWS;
        info.os_family_str = "Windows";
        info.default_shell = "PowerShell / cmd.exe";
        info.suggested_pkg_manager = "winget / choco / vcpkg";
        info.compiler_toolchain = "MSVC (cl.exe) / MinGW (g++) / clang-cl";

        SYSTEM_INFO sysInfo;
        GetNativeSystemInfo(&sysInfo);
        info.cpu_threads = sysInfo.dwNumberOfProcessors;

        switch (sysInfo.wProcessorArchitecture) {
            case PROCESSOR_ARCHITECTURE_AMD64: info.architecture = "x86_64 (64-bit)"; break;
            case PROCESSOR_ARCHITECTURE_ARM64: info.architecture = "ARM64"; break;
            case PROCESSOR_ARCHITECTURE_INTEL: info.architecture = "x86 (32-bit)"; break;
            default: info.architecture = "Unknown Architecture"; break;
        }

        MEMORYSTATUSEX memStatus;
        memStatus.dwLength = sizeof(memStatus);
        if (GlobalMemoryStatusEx(&memStatus)) {
            info.total_ram_mb = memStatus.ullTotalPhys / (1024 * 1024);
            info.free_ram_mb = memStatus.ullAvailPhys / (1024 * 1024);
        }
        info.os_name = "Microsoft Windows";
        info.kernel_version = "NT Kernel";

#elif defined(PLATFORM_MACOS)
        info.family = OSFamily::UNIX_MACOS;
        info.os_family_str = "Unix (macOS / Darwin)";
        info.default_shell = "zsh / bash";
        info.suggested_pkg_manager = "Homebrew (brew)";
        info.compiler_toolchain = "Apple Clang (clang++) / Xcode CLI";

        struct utsname uts;
        if (uname(&uts) == 0) {
            info.os_name = std::string("macOS ") + uts.sysname;
            info.kernel_version = uts.release;
            info.architecture = uts.machine;
        }

        int mib[2] = {CTL_HW, HW_NCPU};
        int numCPU = 1;
        size_t len = sizeof(numCPU);
        sysctl(mib, 2, &numCPU, &len, NULL, 0);
        info.cpu_threads = numCPU;

        int64_t mem = 0;
        mib[1] = HW_MEMSIZE;
        len = sizeof(mem);
        sysctl(mib, 2, &mem, &len, NULL, 0);
        info.total_ram_mb = mem / (1024 * 1024);
        info.free_ram_mb = info.total_ram_mb / 2; // Approximated estimate

#elif defined(PLATFORM_UNIX)
        info.family = OSFamily::UNIX_LINUX;
        info.os_family_str = "Unix (Linux)";
        info.default_shell = "bash / sh";
        info.compiler_toolchain = "GCC (g++) / Clang (clang++)";

        struct utsname uts;
        if (uname(&uts) == 0) {
            info.kernel_version = uts.release;
            info.architecture = uts.machine;
        }

        // Parse Linux distro name
        info.os_name = "Linux Generic";
        info.suggested_pkg_manager = "apt / pacman / dnf";
        std::ifstream osRelease("/etc/os-release");
        if (osRelease.is_open()) {
            std::string line;
            while (std::getline(osRelease, line)) {
                if (line.rfind("PRETTY_NAME=", 0) == 0 || line.rfind("NAME=", 0) == 0) {
                    size_t first = line.find('"');
                    size_t last = line.rfind('"');
                    if (first != std::string::npos && last != std::string::npos && last > first) {
                        info.os_name = line.substr(first + 1, last - first - 1);
                        break;
                    }
                }
            }
        }

        // Determine specific Linux package manager
        if (info.os_name.find("Arch") != std::string::npos || info.os_name.find("Manjaro") != std::string::npos) {
            info.suggested_pkg_manager = "pacman";
        } else if (info.os_name.find("Ubuntu") != std::string::npos || info.os_name.find("Debian") != std::string::npos) {
            info.suggested_pkg_manager = "apt / apt-get";
        } else if (info.os_name.find("Fedora") != std::string::npos || info.os_name.find("RHEL") != std::string::npos) {
            info.suggested_pkg_manager = "dnf";
        }

        info.cpu_threads = sysconf(_SC_NPROCESSORS_ONLN);

        struct sysinfo si;
        if (sysinfo(&si) == 0) {
            info.total_ram_mb = (si.totalram * si.mem_unit) / (1024 * 1024);
            info.free_ram_mb = (si.freeram * si.mem_unit) / (1024 * 1024);
        }
#else
        info.family = OSFamily::UNKNOWN;
        info.os_family_str = "Unknown Generic OS";
        info.os_name = "Generic Platform";
        info.architecture = "unknown";
        info.default_shell = "sh";
        info.suggested_pkg_manager = "manual";
        info.compiler_toolchain = "cc / c++";
#endif

        return info;
    }
};
