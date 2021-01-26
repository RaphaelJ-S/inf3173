OPT=gcc -std=c11 -Werror -Wall -Wpedantic

all: prime

clean :
	rm ./prime

prime: prime.c
	$(OPT) -lm -o prime prime.c

.PHONY: all clean
