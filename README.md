# THE NULL - Central AI Workforce Commander Controller

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows%20%7C%20macOS-lightgrey.svg)]()
[![Inference Engine](https://img.shields.io/badge/Inference-llama.cpp%20%2F%20ggml-orange.svg)](https://github.com/ggml-org/llama.cpp)
[![Architecture](https://img.shields.io/badge/Architecture-SOLID%20Modular%20C%2B%2B-brightgreen.svg)]()

**THE NULL Commander** is a lightweight, high-performance autonomous task orchestration engine written in modern C++ (C++17). Running directly on bare-metal inference using `llama.cpp` and `ggml`, THE NULL operates with zero Python overhead to analyze arbitrary user requests, inspect host operating systems and hardware resources, and autonomously generate end-to-end, execution-ready JSON engineering blueprints across **10 specialized divisions**.

---

## 🌟 Key Features

- **Zero-Overhead Native C++ Engine**: Runs local quantized GGUF models directly via C/C++ llama bindings with AVX2/FMA optimizations.
- **Dynamic Host OS & Hardware Discovery**:
  - Live detection of OS Family (Linux, Windows, macOS), distribution, kernel version, hardware architecture.
  - Telemetry probing for available CPU threads, total physical RAM, and free real-time memory.
  - Automatically identifies host package managers (`pacman`, `apt`, `brew`, `winget`) and default shells.
- **Universal Domain Adaptability**:
  - Dynamically plans for **any** programming language or domain: Web backends (Laravel, Node.js, Go), systems programming (C/C++, Rust), Python ML/data pipelines, multimedia/video processing (`ffmpeg`), DevOps, etc.
- **Unrestricted End-to-End Planning**:
  - Dynamic step count adapted to task complexity (scaffold $\to$ domain entities $\to$ core business logic $\to$ authentication/security $\to$ automated testing $\to$ delivery).
  - Never truncates or substitutes steps with placeholder comments.
- **Calibrated Token Sampling for JSON Schemas**:
  - Custom sampler chain with decoupled frequency/presence penalties to prevent key suppression across repetitive schema arrays (`step_id`, `division`, `action`, `command`, `target_files`, `verification`).
  - String-aware JSON brace balancing in `ChatEngine` to prevent premature termination when commands contain unescaped shell braces (e.g. `awk '{...}'`).
- **SOLID Modular Architecture**:
  - Decoupled interfaces for formatters, prompt loaders (Decorator pattern), samplers, and engine orchestration.

---

## 🏛 The 10 Specialized Divisions

Every generated blueprint maps sequential actions to dedicated operational divisions:

| Division Code | Operational Scope | Typical CLI Tools & Stacks |
| :--- | :--- | :--- |
| `DIV_01_VISION` | Video editing, computer vision, OCR, UI layout perception | `ffmpeg`, `gimp`, OpenCV, OCR engines |
| `DIV_02_EXECUTION` | Automated testing suites, builds, assertion validation | `phpunit`, `pytest`, `jest`, `ctest`, `cargo test` |
| `DIV_03_PLANNING` | Directory layout, scaffolding, config files, modular layout | `composer create-project`, `npm init`, `cargo new` |
| `DIV_04_STORAGE` | Database schemas, migrations, Eloquent/ORM models, Redis caching | `php artisan make:migration`, `prisma`, SQL migrations |
| `DIV_05_DOCUMENTS` | Ingestion of BRDs, PDF specs, text requirements *(only when provided)* | `pdftotext`, text extraction tools |
| `DIV_06_SECURITY` | Authentication (Sanctum/JWT/OAuth), security policies, tokens | Auth providers, security middleware, encryption |
| `DIV_07_AUDIO` | Audio transcoding, synthesis, sound track mixing, Whisper transcription | `ffmpeg`, `sox`, Whisper CLI |
| `DIV_08_NETWORK` | RESTful APIs, HTTP controllers, routing, endpoint contracts | Resource controllers, routes, API clients |
| `DIV_09_COMPUTATION` | Core domain algorithms, numerical processing, business logic | Mathematical pipelines, algorithm implementations |
| `DIV_10_DELIVERY` | Service startup, background daemons, health checks, release artifacts | `php artisan serve`, `systemctl`, `curl`, Docker |

---

## 📂 Project Architecture

```
null-project/
├── include/
│   ├── core/
│   │   ├── LlamaModel.hpp           # RAII wrapper around llama_model & vocabulary
│   │   ├── LlamaContext.hpp         # RAII wrapper around llama_context & KV cache decoding
│   │   └── PlatformDetector.hpp     # Cross-platform host OS, RAM & CPU discovery
│   ├── formatters/
│   │   ├── IChatFormatter.hpp       # Chat template formatting abstraction
│   │   └── QwenChatMLFormatter.hpp  # ChatML formatting with assistant JSON prefilling
│   ├── loaders/
│   │   ├── IPromptLoader.hpp        # Prompt loading interface
│   │   ├── FilePromptLoader.hpp     # Loads base prompt from disk
│   │   ├── StaticPromptLoader.hpp   # In-memory prompt loader
│   │   └── SystemAwarePromptLoader.hpp # Decorator: Injects live OS & hardware telemetry
│   ├── samplers/
│   │   ├── ISampler.hpp             # Sampler interface
│   │   ├── GreedySampler.hpp        # Greedy argmax sampler
│   │   └── ConfigurableSampler.hpp  # Repetition penalties, Top-K/Top-P, temperature
│   └── engine/
│       └── ChatEngine.hpp           # Lifecycle coordinator with string-aware JSON tracking
├── models/
│   └── commanders/                  # Quantized GGUF models (e.g. Qwen2.5 1.5B Instruct)
├── ggml/                            # GGML submodule (tensor library)
├── llama.cpp/                       # llama.cpp submodule (LLM inference backend)
├── system_prompt.txt                # Universal domain-agnostic commander prompt
├── chat.cpp                         # Composition Root & terminal REPL loop
├── Makefile                         # Native build script with SIMD flags (-mavx2 -mfma)
├── the_null_architecture_and_data_flow.drawio          # System architecture diagram
└── the_null_ram_allocation_and_memory_management.drawio # RAM allocation diagram
```

---

---

## 💻 System & Hardware Requirements

| Requirement | Minimum Specification | Recommended Specification |
| :--- | :--- | :--- |
| **Operating System** | Linux (Arch, Ubuntu, Debian, Fedora), macOS 12+, Windows 10/11 (64-bit) | Linux (x86_64 or aarch64) or macOS (Apple Silicon M-series) |
| **CPU Architecture** | x86_64 with AVX2/FMA or ARM64 (ARMv8.2-A / NEON) | x86_64 with AVX-512 or Apple Silicon (M1/M2/M3/M4) |
| **CPU Cores** | 2 cores (4 threads) | 6 to 12+ physical cores |
| **RAM (1.5B GGUF)** | **2 GB free RAM** | **4 GB RAM** |
| **RAM (7B+ GGUF)** | **8 GB free RAM** | **16 GB RAM** |
| **Disk Storage** | 2.5 GB for code & build artifacts | 10+ GB to store multiple GGUF models |
| **Compilers & Tools**| C++17 compiler (GCC 9+, Clang 10+, Apple Clang 12+, MSVC 2022), CMake 3.16+, Git |

> 📖 **Looking for in-depth platform details, GPU/CUDA acceleration, or troubleshooting?**  
> Check the full [Cross-Platform Compilation & Requirements Guide](docs/COMPILATION_GUIDE.md).

---

## 🚀 Quick Start & Compilation

### Step 1: Clone Repository & Submodules
```bash
git clone --recurse-submodules https://github.com/Ahmedfargh/ai-cpp.git
cd ai-cpp
```
If already cloned without submodules:
```bash
git submodule update --init --recursive
```

---

### Step 2: Build by Operating System

#### 🐧 Linux (Arch / Ubuntu / Debian / Fedora)
```bash
# 1. Build GGML and llama.cpp shared libraries
cmake -B ggml/build -S ggml -DCMAKE_BUILD_TYPE=Release -DGGML_BUILD_EXAMPLES=OFF -DGGML_BUILD_TESTS=OFF
cmake --build ggml/build --config Release -j$(nproc)

cmake -B llama.cpp/build -S llama.cpp -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DLLAMA_BUILD_EXAMPLES=OFF -DLLAMA_BUILD_TESTS=OFF
cmake --build llama.cpp/build --config Release -j$(nproc)

# 2. Build THE NULL Commander
make

# 3. Run
make run
# Or directly:
LD_LIBRARY_PATH=./ggml/build/src:./llama.cpp/build/bin ./qwen_chat
```

#### 🍎 macOS (Apple Silicon M-Series & Intel)
```bash
# 1. Build GGML and llama.cpp (with Apple Metal acceleration enabled)
cmake -B ggml/build -S ggml -DCMAKE_BUILD_TYPE=Release -DGGML_BUILD_EXAMPLES=OFF -DGGML_BUILD_TESTS=OFF
cmake --build ggml/build --config Release -j$(sysctl -n hw.ncpu)

cmake -B llama.cpp/build -S llama.cpp -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DGGML_METAL=ON -DLLAMA_BUILD_EXAMPLES=OFF -DLLAMA_BUILD_TESTS=OFF
cmake --build llama.cpp/build --config Release -j$(sysctl -n hw.ncpu)

# 2. Compile qwen_chat with clang++
clang++ -std=c++17 -O3 chat.cpp -I include -I ggml/include -I ggml/ggml/include -I llama.cpp/include -I llama.cpp/ggml/include -L ggml/build/src -L llama.cpp/build/bin -lllama -lggml -lggml-base -lggml-cpu -o qwen_chat

# 3. Run
DYLD_LIBRARY_PATH=./ggml/build/src:./llama.cpp/build/bin ./qwen_chat
```

#### 🪟 Windows (Visual Studio 2022 / MSVC / PowerShell)
Open the **x64 Native Tools Command Prompt for VS 2022**:
```cmd
REM 1. Build GGML and llama.cpp DLLs
cmake -B ggml/build -S ggml -G "Visual Studio 17 2022" -A x64 -DGGML_BUILD_EXAMPLES=OFF -DGGML_BUILD_TESTS=OFF
cmake --build ggml/build --config Release --parallel %NUMBER_OF_PROCESSORS%

cmake -B llama.cpp/build -S llama.cpp -G "Visual Studio 17 2022" -A x64 -DBUILD_SHARED_LIBS=ON -DLLAMA_BUILD_EXAMPLES=OFF -DLLAMA_BUILD_TESTS=OFF
cmake --build llama.cpp/build --config Release --parallel %NUMBER_OF_PROCESSORS%

REM 2. Compile qwen_chat.exe with MSVC
cl /std:c++17 /O2 /EHsc /utf-8 chat.cpp /I include /I ggml\include /I ggml\ggml\include /I llama.cpp\include /I llama.cpp\ggml\include /link /LIBPATH:ggml\build\src\Release /LIBPATH:llama.cpp\build\bin\Release llama.lib ggml.lib ggml-base.lib ggml-cpu.lib /out:qwen_chat.exe

REM 3. Copy DLLs and Run
copy ggml\build\src\Release\*.dll .
copy llama.cpp\build\bin\Release\*.dll .
qwen_chat.exe
```

---

### Step 3: Model Weights Placement
Place any compatible GGUF quantized model (e.g. Qwen2.5 1.5B Instruct) inside the `models/commanders/` folder:
```bash
models/commanders/josiefied-qwen2.5-1.5b-instruct-abliterated-v1.IQ4_XS.gguf
```
*(The model path can be customized on line 22 of [chat.cpp](chat.cpp)).*

---

## 📋 Example Usage & Output

### Input:
```
You: build laravel backend for blog use sanctum apis for it
```

### Generated JSON Execution Blueprint:
```json
{
  "plan_id": "laravel_backend_001",
  "project_name": "blog_backend",
  "target_goal": "Build a complete Laravel blog backend with Sanctum API authentication",
  "architecture": "Modular RESTful API with Token Authentication",
  "status": "READY_FOR_EXECUTION",
  "models_loaded": 0,
  "steps": [
    {
      "step_id": 1,
      "division": "DIV_03_PLANNING",
      "action": "Scaffold Laravel project workspace and install Sanctum package",
      "command": "composer create-project laravel/laravel blog-api && cd blog-api && composer require laravel/sanctum",
      "target_files": ["composer.json", ".env"],
      "dependencies": [],
      "verification": "test -f blog-api/artisan",
      "expected_output": "Laravel project initialized with Sanctum package installed"
    },
    {
      "step_id": 2,
      "division": "DIV_04_STORAGE",
      "action": "Generate database migrations and Eloquent models for blog posts and categories",
      "command": "cd blog-api && php artisan make:model Post -m && php artisan make:model Category -m",
      "target_files": ["app/Models/Post.php", "app/Models/Category.php", "database/migrations"],
      "dependencies": [1],
      "verification": "test -f blog-api/app/Models/Post.php && test -f blog-api/app/Models/Category.php",
      "expected_output": "Database migration files and Eloquent models created"
    },
    {
      "step_id": 3,
      "division": "DIV_06_SECURITY",
      "action": "Publish Sanctum configuration and implement Sanctum API authentication controller",
      "command": "cd blog-api && php artisan vendor:publish --provider=\"Laravel\\Sanctum\\SanctumServiceProvider\" && php artisan make:controller Api/AuthController",
      "target_files": ["config/sanctum.php", "app/Http/Controllers/Api/AuthController.php"],
      "dependencies": [1],
      "verification": "test -f blog-api/config/sanctum.php",
      "expected_output": "Sanctum published and AuthController generated for token issuance"
    },
    {
      "step_id": 4,
      "division": "DIV_08_NETWORK",
      "action": "Create RESTful API controllers and configure protected API endpoints in routes/api.php",
      "command": "cd blog-api && php artisan make:controller Api/PostController --api && php artisan make:controller Api/CategoryController --api",
      "target_files": ["app/Http/Controllers/Api/PostController.php", "routes/api.php"],
      "dependencies": [2, 3],
      "verification": "test -f blog-api/app/Http/Controllers/Api/PostController.php",
      "expected_output": "API routes and resource controllers created with Sanctum auth middleware"
    },
    {
      "step_id": 5,
      "division": "DIV_02_EXECUTION",
      "action": "Run database migrations and execute feature test suite for Sanctum authentication and CRUD APIs",
      "command": "cd blog-api && php artisan migrate --force && php artisan make:test PostApiTest && php artisan test",
      "target_files": ["tests/Feature/PostApiTest.php"],
      "dependencies": [4],
      "verification": "cd blog-api && php artisan test",
      "expected_output": "Database migrated and all automated feature tests passing"
    },
    {
      "step_id": 6,
      "division": "DIV_10_DELIVERY",
      "action": "Launch local development server and perform live API endpoint health check",
      "command": "cd blog-api && php artisan serve --port=8000 & sleep 2 && curl -I http://127.0.0.1:8000/api/posts",
      "target_files": ["blog-api"],
      "dependencies": [5],
      "verification": "curl -s -o /dev/null -w \"%{http_code}\" http://127.0.0.1:8000/api/posts",
      "expected_output": "Live Laravel server listening on port 8000 responding with valid HTTP status"
    }
  ]
}
```

---

## 🛠 Advanced Configuration

All inference and sampling parameters are configurable in [chat.cpp](chat.cpp) and [ConfigurableSampler.hpp](include/samplers/ConfigurableSampler.hpp):

- **Context Window**: 4096 tokens (supports deep system prompt and large multi-step roadmaps)
- **Max Turn Tokens**: 3072 tokens
- **Inference Threads**: 6 CPU threads (tuned for hyperthreaded x86_64 host)
- **Sampler Calibration**:
  - `temperature`: `0.3f`
  - `top_p`: `0.95f`
  - `repeat_penalty`: `1.03f` (tuned to allow JSON schema key repetition while suppressing loops)
  - `penalty_freq`: `0.0f`
  - `penalty_present`: `0.0f`

---

## 📄 License
This project is licensed under the MIT License.
