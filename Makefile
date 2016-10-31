CXX = g++
CXXFLAGS  = -std=c++11 -O2 -Wall
TARGET = $1
  
all: $(TARGET)
$(TARGET): $(TARGET).cpp ; $(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET).cpp
