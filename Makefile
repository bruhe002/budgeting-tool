SOURCE=src

all: build run

build:
	g++ -c src/users/interface.cpp -o builds/interface.o
	g++ builds/interface.o -o builds/interface.exe
	g++ -c src/main.cpp -o builds/main.o
	g++ -c src/budget/Budget.cpp -o builds/Budget.o
	g++ builds/main.o builds/Budget.o -o builds/main.exe

run:
	builds/main.exe

sign-up:
	builds/interface.exe
