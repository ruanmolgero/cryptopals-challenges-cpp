CXX = g++  # C++ compiler
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude  # Compiler flags and include directories

# List of source files
SRCS = main.cpp util.cpp

# Generate a list of object files from the source files
OBJS = $(SRCS:.cpp=.o)

# The name of the executable
TARGET = my_project

.PHONY: all clean run

# Default target: build the executable
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to compile a source file into an object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the executable
run: $(TARGET)
	clear
	./$(TARGET)

# Clean up the generated files
clean:
	rm -f $(OBJS) $(TARGET)

