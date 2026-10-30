CXX = g++
CXXFLAGS = -std=c++17 -O3 -mavx2 -mfma -Wall -Wextra

# Include paths
INCLUDES = -I include \
           -I ggml/include -I ggml/ggml/include \
           -I llama.cpp/include -I llama.cpp/ggml/include

# Library paths
LIBS = -L ggml/build/src \
       -L llama.cpp/build/bin \
       -lllama -lggml -lggml-base -lggml-cpu

# Discover all implementation source files
SRCS = $(wildcard src/*/*.cpp)
OBJS = $(SRCS:.cpp=.o)

# Run environment variable
RUN_ENV = LD_LIBRARY_PATH=./ggml/build/src:./llama.cpp/build/bin

all: qwen_chat

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

qwen_chat: chat.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) chat.cpp $(OBJS) $(INCLUDES) $(LIBS) -o qwen_chat

run: qwen_chat
	$(RUN_ENV) ./qwen_chat

clean:
	rm -f qwen_chat $(OBJS)

.PHONY: all run clean