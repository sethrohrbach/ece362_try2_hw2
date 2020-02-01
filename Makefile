all: tx twist xor

tx: tx.c
	gcc -std=c99 -Wall -o tx tx.c
twist: twist.c
	gcc -std=c99 -Wall -o twist twist.c
xor: xor.c
	gcc -std=c99 -Wall -o xor xor.c
make clean:
	rm twist.o xor.o tx.o
