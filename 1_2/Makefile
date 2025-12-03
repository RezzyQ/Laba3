CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = 

TARGET = route_cipher
TEST_TARGET = test_route_cipher

all: $(TARGET) $(TEST_TARGET)

$(TARGET): main.o RouteCipher.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_TARGET): test_RouteCipher_quick.o RouteCipher.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

main.o: main.cpp RouteCipher.h
	$(CXX) $(CXXFLAGS) -c main.cpp

RouteCipher.o: RouteCipher.cpp RouteCipher.h
	$(CXX) $(CXXFLAGS) -c RouteCipher.cpp

test_RouteCipher_quick.o: test_RouteCipher_quick.cpp RouteCipher.h
	$(CXX) $(CXXFLAGS) -c test_RouteCipher_quick.cpp

clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

.PHONY: all clean run test
