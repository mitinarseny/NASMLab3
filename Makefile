.PHONY: build
build: lab3

lab3: main.c
	gcc --std=c11 -Wall -O3 -masm=intel -o $@ $^
