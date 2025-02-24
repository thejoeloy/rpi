# Makefile for compiling playback.cpp with OpenCV

# Compiler and linker settings
CXX = g++
CXXFLAGS = -std=c++11 `pkg-config --cflags opencv4`
LDFLAGS = `pkg-config --libs opencv4`

# Target name (output binary)
TARGET = playback

# Source files
SRC = playback.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Default target to build the executable
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Rule to compile the source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJ) $(TARGET)

# Run the program after compilation
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run

