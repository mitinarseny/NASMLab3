CC := gcc
CFLAGS := --std=c11 -Wall -O3

.PHONY: build
build: lab3

lab3: main.c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: asm
asm: main.c
	$(CC) $(CFLAGS) -S -o /dev/stdout $^ | less
