CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -lssl -lcrypto
DEPFLAGS = -Wno-deprecated-declarations
# Target executable name
TARGET = blockchain_app

# Source files
SRCS = main.cpp

# Default rule
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS) $(DEPFLAGS)

clean:
	rm -f $(TARGET)