CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude

CHALLENGES = challenge_11 challenge_12 challenge_13
SRCS = $(addsuffix .cpp, $(CHALLENGES))
OBJS = $(SRCS:.cpp=.o)

all: $(CHALLENGES)

$(CHALLENGES): % : %.o util.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp util.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(CHALLENGES)