all: main
main: main.c ../src/parse_transaction.c
		cc -o main -I ../src main.c ../src/parse_transaction.c
test: main
		./main