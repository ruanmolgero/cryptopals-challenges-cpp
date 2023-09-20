CXX = g++
CXXFLAGS = -std=c++11 -Wall
SRCS = main.cpp
TARGET = myapp

$(TARGET): $(SRCS)
    $(CXX) $(CXXFLAGS) -o $@ $^

clean:
    rm -f $(TARGET)