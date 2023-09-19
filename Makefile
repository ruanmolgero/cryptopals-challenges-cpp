# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Source and header files
SRCS = cryptopals_s1.cpp #s13.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

# Output executable name
TARGET = myapp

# Build rule for the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Build rule for object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build rule for dependency files
%.d: %.cpp
	$(CXX) -MM $(CXXFLAGS) $< | sed 's/$*\.o/& $@/' > $@

# Include dependency files if they exist
-include $(DEPS)

.PHONY: clean

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)
