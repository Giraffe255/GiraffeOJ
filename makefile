server:server.cpp
	g++ $^ -o $@ -lpthread -std=c++11

.PHONY:clean
clean:
	rm server
