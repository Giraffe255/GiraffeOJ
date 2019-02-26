test:test.cpp
	g++ $^ -o $@ -lpthread -std=c++11 -ljsoncpp

.PHONY:clean
clean:
	rm test
