SOURCE=src

all: build run

build:
	g++ -o main src/main.cpp src/budget/Budget.cpp

run:
	./main.exe