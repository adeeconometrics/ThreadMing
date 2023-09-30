# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -pthread
BUILD_DIR := build
SRC_DIR := src
INCLUDE_DIR := include

# Include directories
INC_FLAGS := -I$(INCLUDE_DIR)

# Find all source files in the SRC_DIR
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)

# Generate object file names in the BUILD_DIR
BUILD_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Main target: specify the name of your final executable
TARGET := my_program

# Rule to build object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INC_FLAGS) -c -o $@ $<

# Rule to build the final executable
$(TARGET): $(BUILD_FILES)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $^ $(LDFLAGS)

# Clean up generated files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
