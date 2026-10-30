# THE NULL Commander - Cross-Platform Compilation & Requirements Guide

This document provides complete instructions for building, configuring, and running **THE NULL Commander Controller** across **Linux**, **macOS**, and **Windows**.

---

## 💻 Hardware & System Requirements

### 1. Hardware Requirements

| Component | Minimum Specification (1.5B Model) | Recommended Specification (7B+ Models) |
| :--- | :--- | :--- |
| **CPU Architecture** | x86_64 (with AVX2 & FMA) or ARM64 (ARMv8.2-A / NEON) | x86_64 with AVX-512 or Apple Silicon (M1/M2/M3/M4) |
| **CPU Cores** | 2 cores (4 threads) | 6 to 12+ physical cores |
| **System RAM** | **2 GB free RAM** for 1.5B Q4/Q5 quantized models | **8 GB free RAM** for 7B models; **16 GB** for 14B models |
| **Disk Space** | 2.5 GB (Build toolchain, dependencies, and artifacts) | 10+ GB (to store multiple GGUF quantized models) |
| **GPU (Optional)** | Not required (CPU inference supported out-of-the-box) | NVIDIA GPU (CUDA), Apple Silicon (Metal), or Vulkan GPU |

### 2. Software Requirements by Operating System

| OS | Supported Versions | Required Compilers & Tools |
| :--- | :--- | :--- |
| **Linux** | Arch Linux, Ubuntu 20.04+, Debian 11+, Fedora 36+, RHEL/Rocky 8+ | GCC 9+ or Clang 10+, CMake 3.16+, Make, Git |
| **macOS** | macOS 12 (Monterey) or newer (Apple Silicon & Intel) | Xcode Command Line Tools (Apple Clang 12+), CMake, Git |
| **Windows** | Windows 10 / 11 (64-bit) | Visual Studio 2022 (MSVC v143) or MinGW-w64 (GCC 10+), CMake, Git |

---

## 📦 Step 0: Clone Repository & Submodules

Ensure you clone recursively to pull both `ggml` and `llama.cpp`:

```bash
git clone --recurse-submodules https://github.com/Ahmedfargh/ai-cpp.git
cd ai-cpp
```

If you previously cloned without `--recurse-submodules`, initialize them manually:
```bash
git submodule update --init --recursive
```

---

## 🐧 Linux Compilation Guide

### 1. Install Dependencies

**Arch Linux / Manjaro:**
```bash
sudo pacman -S base-devel cmake git
```

**Ubuntu / Debian / Linux Mint:**
```bash
sudo apt update
sudo apt install -y build-essential cmake git
```

**Fedora / RHEL / Rocky Linux:**
```bash
sudo dnf groupinstall -y "Development Tools"
sudo dnf install -y cmake git
```

---

### 2. Build GGML and llama.cpp Shared Libraries

Build the GGML tensor library:
```bash
cmake -B ggml/build -S ggml \
    -DCMAKE_BUILD_TYPE=Release \
    -DGGML_BUILD_EXAMPLES=OFF \
    -DGGML_BUILD_TESTS=OFF

cmake --build ggml/build --config Release -j$(nproc)
```

Build the llama.cpp engine:
```bash
cmake -B llama.cpp/build -S llama.cpp \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=ON \
    -DLLAMA_BUILD_EXAMPLES=OFF \
    -DLLAMA_BUILD_TESTS=OFF \
    -DLLAMA_BUILD_SERVER=OFF

cmake --build llama.cpp/build --config Release -j$(nproc)
```

---

### 3. Compile THE NULL Commander

Using the included `Makefile`:
```bash
make
```

Or manually via `g++`:
```bash
g++ -std=c++17 -O3 -mavx2 -mfma chat.cpp \
    -I include \
    -I ggml/include -I ggml/ggml/include \
    -I llama.cpp/include -I llama.cpp/ggml/include \
    -L ggml/build/src \
    -L llama.cpp/build/bin \
    -lllama -lggml -lggml-base -lggml-cpu \
    -o qwen_chat
```

---

### 4. Run on Linux

Set `LD_LIBRARY_PATH` so the dynamic linker finds `libllama.so` and `libggml.so`:

```bash
LD_LIBRARY_PATH=./ggml/build/src:./llama.cpp/build/bin ./qwen_chat
```
Or simply:
```bash
make run
```

---

## 🍎 macOS Compilation Guide (Apple Silicon & Intel)

### 1. Install Prerequisites

Install Apple Xcode Command Line Tools:
```bash
xcode-select --install
```

Install Homebrew (if not already installed), then install CMake:
```bash
brew install cmake git
```

---

### 2. Build GGML and llama.cpp Shared Libraries

On macOS (specifically Apple Silicon M1/M2/M3/M4), Metal acceleration provides maximum inference speed:

**Build GGML:**
```bash
cmake -B ggml/build -S ggml \
    -DCMAKE_BUILD_TYPE=Release \
    -DGGML_BUILD_EXAMPLES=OFF \
    -DGGML_BUILD_TESTS=OFF

cmake --build ggml/build --config Release -j$(sysctl -n hw.ncpu)
```

**Build llama.cpp (with Apple Metal enabled):**
```bash
cmake -B llama.cpp/build -S llama.cpp \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=ON \
    -DGGML_METAL=ON \
    -DLLAMA_BUILD_EXAMPLES=OFF \
    -DLLAMA_BUILD_TESTS=OFF

cmake --build llama.cpp/build --config Release -j$(sysctl -n hw.ncpu)
```

*(Note: On Intel Macs, omit `-DGGML_METAL=ON` if you only want CPU inference).*

---

### 3. Compile THE NULL Commander on macOS

Using `clang++`:
```bash
clang++ -std=c++17 -O3 chat.cpp \
    -I include \
    -I ggml/include -I ggml/ggml/include \
    -I llama.cpp/include -I llama.cpp/ggml/include \
    -L ggml/build/src \
    -L llama.cpp/build/bin \
    -lllama -lggml -lggml-base -lggml-cpu \
    -o qwen_chat
```

---

### 4. Run on macOS

Set `DYLD_LIBRARY_PATH` so macOS dynamic loader finds the `.dylib` files:

```bash
DYLD_LIBRARY_PATH=./ggml/build/src:./llama.cpp/build/bin ./qwen_chat
```

---

## 🪟 Windows Compilation Guide (MSVC & PowerShell)

### 1. Prerequisites

1. Install **Visual Studio 2022** (Community, Professional, or Enterprise) or **Visual Studio Build Tools**.
   - In the Visual Studio Installer, ensure **"Desktop development with C++"** is selected.
   - Ensure **CMake tools for Windows** is checked.
2. Install **Git for Windows**.

Open the **x64 Native Tools Command Prompt for VS 2022** (or PowerShell with developer environment initialized).

---

### 2. Build GGML and llama.cpp Shared Libraries (DLLs)

**Build GGML:**
```cmd
cmake -B ggml/build -S ggml ^
    -G "Visual Studio 17 2022" -A x64 ^
    -DGGML_BUILD_EXAMPLES=OFF ^
    -DGGML_BUILD_TESTS=OFF

cmake --build ggml/build --config Release --parallel %NUMBER_OF_PROCESSORS%
```

**Build llama.cpp:**
```cmd
cmake -B llama.cpp/build -S llama.cpp ^
    -G "Visual Studio 17 2022" -A x64 ^
    -DBUILD_SHARED_LIBS=ON ^
    -DLLAMA_BUILD_EXAMPLES=OFF ^
    -DLLAMA_BUILD_TESTS=OFF

cmake --build llama.cpp/build --config Release --parallel %NUMBER_OF_PROCESSORS%
```

---

### 3. Compile THE NULL Commander on Windows (MSVC)

Compile with Microsoft C/C++ compiler (`cl.exe`):

```cmd
cl /std:c++17 /O2 /EHsc /utf-8 chat.cpp ^
    /I include ^
    /I ggml\include /I ggml\ggml\include ^
    /I llama.cpp\include /I llama.cpp\ggml\include ^
    /link /LIBPATH:ggml\build\src\Release ^
          /LIBPATH:llama.cpp\build\bin\Release ^
          llama.lib ggml.lib ggml-base.lib ggml-cpu.lib ^
    /out:qwen_chat.exe
```

---

### 4. Run on Windows

Windows searches for DLLs in the same directory as the executable. Copy the compiled DLLs into the same folder as `qwen_chat.exe`:

**In CMD:**
```cmd
copy ggml\build\src\Release\*.dll .
copy llama.cpp\build\bin\Release\*.dll .
qwen_chat.exe
```

**In PowerShell:**
```powershell
Copy-Item ggml\build\src\Release\*.dll .
Copy-Item llama.cpp\build\bin\Release\*.dll .
.\qwen_chat.exe
```

---

## ⚡ Optional: Hardware Acceleration (CUDA / OpenMP)

### NVIDIA CUDA Acceleration (Linux & Windows)
If you have an NVIDIA GPU with the CUDA Toolkit (11.8+ or 12.x) installed:

Add `-DGGML_CUDA=ON` when generating build files for `llama.cpp`:
```bash
cmake -B llama.cpp/build -S llama.cpp \
    -DBUILD_SHARED_LIBS=ON \
    -DGGML_CUDA=ON \
    -DCMAKE_BUILD_TYPE=Release
cmake --build llama.cpp/build --config Release -j$(nproc)
```

In `chat.cpp`, you can adjust GPU offloading layers in `LlamaModel` instantiation:
```cpp
// Change 0 to the number of layers to offload to GPU (e.g. 28)
LlamaModel model(model_path, 28);
```

---

## 🔍 Troubleshooting & FAQ

### 1. `error while loading shared libraries: libllama.so`
**Cause**: The operating system loader cannot locate the built `.so` files.  
**Fix**: Prepend `LD_LIBRARY_PATH` before executing:
```bash
LD_LIBRARY_PATH=./ggml/build/src:./llama.cpp/build/bin ./qwen_chat
```

### 2. `fatal error: llama.h: No such file or directory`
**Cause**: Submodules are missing or uninitialized.  
**Fix**:
```bash
git submodule update --init --recursive
```

### 3. Model file not found / segmentation fault on startup
**Cause**: The path in `chat.cpp` does not match the location of your GGUF model file.  
**Fix**: Ensure your model exists at `./models/commanders/<your-model>.gguf` and the filename in [chat.cpp](../chat.cpp#L22) matches exactly.

### 4. Windows: `The code execution cannot proceed because llama.dll was not found`
**Cause**: Windows looks for `.dll` files in the current working directory or system `PATH`.  
**Fix**: Copy all `.dll` files from `ggml/build/src/Release` and `llama.cpp/build/bin/Release` into the root directory next to `qwen_chat.exe`.
