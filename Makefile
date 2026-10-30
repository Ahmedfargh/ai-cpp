CXX = g++
CXXFLAGS = -std=c++17 -O3 -mavx2 -mfma

# Include paths
INCLUDES = -I include \
           -I ggml/include -I ggml/ggml/include \
           -I llama.cpp/include -I llama.cpp/ggml/include

# The exact library paths
LIBS = -L ggml/build/src \
       -L llama.cpp/build/bin \
       -lllama -lggml -lggml-base -lggml-cpu

# Run env variable
RUN_ENV = LD_LIBRARY_PATH=./ggml/build/src:./llama.cpp/build/bin

all: qwen_chat

qwen_chat: chat.cpp
	$(CXX) $(CXXFLAGS) chat.cpp $(INCLUDES) $(LIBS) -o qwen_chat

run: qwen_chat
	$(RUN_ENV) ./qwen_chat

clean:
	rm -f qwen_chat