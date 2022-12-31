
i = $(wildcard *.c)
OUT = main

$(OUT): $(i)
	gcc -o $@ $^ -lGL -lGLEW -lglfw -lm
