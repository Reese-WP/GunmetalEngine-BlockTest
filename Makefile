# Set up required environment
# Define variables for paths and flags
RAYLIB_PATH = C:\raylib\raylib
RAYLIB_CPP_PATH = C:\raylib-cpp-master
COMPILER_PATH = C:\raylib\w64devkit\bin
CC = g++
CFLAGS = $(RAYLIB_PATH)\src\raylib.rc.data -s -static -Os -Wall -I$(RAYLIB_PATH)\src -Iexternal -DPLATFORM_DESKTOP -Iheaders -I$(RAYLIB_CPP_PATH)\include -I$(SRCDIR) -g
LDFLAGS = -l$(RAYLIB_CPP_PATH)\include\raylib.hpp -lopengl32 -lgdi32 -lwinmm -l$(RAYLIB_CPP_PATH)\include\raylib-cpp.hpp
SRCDIR = src
BINDIR = bin

# Add the compiler path to the system PATH
export PATH := $(COMPILER_PATH):$(PATH)

# Default target
all: $(BINDIR)/main.exe

# Clean latest build
# Remove the executable if it exists
clean:
	@if [ -f $(BINDIR)/main.exe ]; then rm -f $(BINDIR)/main.exe; fi

# Collect all .cpp files
# Find all .cpp files in the source directory and its subdirectories
SRCS := $(shell find $(SRCDIR) -name '*.cpp')

# Compile program
# Compile the collected .cpp files into an executable
$(BINDIR)/main.exe: $(SRCS)
	$(CC) --version
	$(CC) -o $@ $(SRCS) $(CFLAGS) $(LDFLAGS)

# Execute program
# Run the executable if it exists
run: $(BINDIR)/main.exe
	@if [ -f $(BINDIR)/main.exe ]; then $(BINDIR)/main.exe; fi

# Reset environment
.PHONY: clean run

