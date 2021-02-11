all: main
main: main.c ../src/*.c ../src/*.h
		cc -o main -I ../src main.c ../src/parse_transaction.c
test: main
		./main