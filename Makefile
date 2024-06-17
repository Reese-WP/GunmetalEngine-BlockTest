# Directories
SRC_DIR := src
HEADER_DIR := headers
BIN_DIR := bin
OBJ_DIR := obj

# Compiler
CXX := g++
CXXFLAGS := -Wall -std=c++17 -I$(HEADER_DIR) -I"C:/raylib-cpp-master/include"
LDFLAGS := -L"C:/raylib/w64devkit/bin" -lraylib -lraylib-cpp

# Find all source files
SRC_FILES := $(shell find $(SRC_DIR) -name '*.cpp')
# Create a list of object files from source files
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Output executable
TARGET := $(BIN_DIR)/main

# Default target
all: $(TARGET)

# Rule for linking the executable
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

# Rule for compiling object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Phony targets
.PHONY: all clean
