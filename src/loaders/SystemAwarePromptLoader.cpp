#include "loaders/SystemAwarePromptLoader.hpp"
#include "core/PlatformDetector.hpp"
#include <iostream>
#include <sstream>
#include <utility>

SystemAwarePromptLoader::SystemAwarePromptLoader(std::unique_ptr<IPromptLoader> base_loader)
    : base_loader_(std::move(base_loader)) {}

std::string SystemAwarePromptLoader::load() const {
    std::string base_prompt = base_loader_ ? base_loader_->load() : "";
    PlatformInfo p = PlatformDetector::detect();

    std::cout << "[OS Discovery] Host Environment: " << p.os_family_str 
              << " | OS: " << p.os_name 
              << " | CPU: " << p.cpu_threads << " threads"
              << " | RAM: " << p.free_ram_mb << "/" << p.total_ram_mb << " MB free"
              << " | Shell: " << p.default_shell << "\n";

    std::stringstream ss;
    ss << base_prompt << "\n\n";
    ss << "==========================================================\n";
    ss << "DISCOVERED HOST OS & HARDWARE ENVIRONMENT (ACT UPON THIS):\n";
    ss << "==========================================================\n";
    ss << "- OS Family: " << p.os_family_str << "\n";
    ss << "- Operating System: " << p.os_name << " (Kernel/Version: " << p.kernel_version << ")\n";
    ss << "- Hardware Architecture: " << p.architecture << "\n";
    ss << "- Available CPU Threads: " << p.cpu_threads << "\n";
    ss << "- Total Physical RAM: " << p.total_ram_mb << " MB\n";
    ss << "- Currently Free/Avail RAM: " << p.free_ram_mb << " MB\n";
    ss << "- Default Host Shell: " << p.default_shell << "\n";
    ss << "- Recommended Package Manager: " << p.suggested_pkg_manager << "\n";
    ss << "- Native Compiler Toolchain: " << p.compiler_toolchain << "\n\n";

    ss << "MANDATORY OS-AWARE INSTRUCTIONS FOR THE COMMANDER:\n";
    if (p.family == OSFamily::WINDOWS) {
        ss << "1. Target Platform is WINDOWS. You MUST produce Windows-native shell commands (PowerShell or CMD.exe).\n";
        ss << "2. Use Windows package managers (e.g., 'winget install <pkg>' or 'choco install <pkg>'); NEVER output bash commands like apt/pacman/brew/sudo.\n";
        ss << "3. Use Windows paths and file operations (e.g. 'mkdir', 'dir', 'del', '\\' backslashes, .exe, .dll, or powershell cmdlets).\n";
        ss << "4. For builds, use MSVC or CMake with Visual Studio generator (e.g., 'cmake -B build -G \"Visual Studio 17 2022\"').\n";
    } else {
        ss << "1. Target Platform is UNIX-BASED (" << p.os_name << "). You MUST produce POSIX/Unix shell commands (bash/sh/zsh).\n";
        ss << "2. Use the native package manager for this distro: '" << p.suggested_pkg_manager << "'. Never output Windows CMD or winget commands.\n";
        ss << "3. Use POSIX paths ('/'), standard flags, and permissions ('chmod +x').\n";
        ss << "4. For any user-requested stack (Python, Node.js, Go, Rust, C/C++, PHP, ffmpeg, etc.), use that ecosystem's native tools and CLI commands. When building native binaries, use '-j" << p.cpu_threads << "'.\n";
    }
    ss << "5. Ensure every task step's memory requirements fit safely within available RAM (" << p.free_ram_mb << " MB).\n";

    return ss.str();
}
