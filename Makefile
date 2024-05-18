SOURCE=src

all: build run

build:
	g++ -c src/users/interface.cpp -o src/users/interface.exe
	g++ -c src/main.cpp -o main.o
	g++ -c src/budget/Budget.cpp -o Budget.o
	g++ main.o Budget.o -o main.exe

run:
	./main.exe

sign-up:
	./src/users/interface.exe
