OPT=gcc -std=c11 -Werror -Wall -Wpedantic

all: prime

clean :
	rm ./prime

prime: prime.c
	$(OPT) -o prime prime.c -lm

.PHONY: all clean
