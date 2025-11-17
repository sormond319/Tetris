# Tetris Makefile
# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++11 -I/usr/include/SDL2 -D_REENTRANT
LDFLAGS := -lSDL2 -lSDL2_ttf

# Directories
SRC_DIR := src
BUILD_DIR := build
TARGET := tetris

# Source files
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS := $(OBJECTS:.o=.d)

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Rebuild everything
rebuild: clean all

# Run the game
run: $(TARGET)
	./$(TARGET)

# Include dependency files
-include $(DEPS)

.PHONY: all clean rebuild run
