SOURCE=src

all: build run

build:
	g++ -c src/main.cpp -o main.o
	g++ -c src/budget/Budget.cpp -o Budget.o
	g++ -I./src/except main.o Budget.o -o main.exe

run:
	./main.exe