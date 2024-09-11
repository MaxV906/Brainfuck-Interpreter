all: bf

bf: main.c
	gcc main.c -o bf

clean:
	rm bf
