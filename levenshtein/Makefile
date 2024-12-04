CC = gcc -g 

.PHONY = all clean

all : lev

clean :
	rm -rf lev_recursive lev_recursive_parallel

lev : lev_recursive.c lev_recursive_parallel.c
	${CC} lev_recursive.c -o lev_recursive
	${CC} lev_recursive_parallel.c -o lev_recursive_parallel -fopenmp

run:
	./lev_recursive
	./lev_recursive_parallel
