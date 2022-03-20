run: all
	./bin/main

all: clean build

build:
	g++ -o bin/main -I ./include -std=c++11 src/main.cpp src/vec3.cpp

clean:
	rm -f bin/* images/*

