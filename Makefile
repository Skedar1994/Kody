CXX = g++
CXXFLAGS  = -std=c++11 -O2 -Wall -Werror -D_GLIBCXX_DEBUG
TARGET = $1
  
all: $(TARGET)
$(TARGET): $(TARGET).cpp ; $(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET).cpp
