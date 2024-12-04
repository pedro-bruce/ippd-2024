CC = gcc 

.PHONY = all clean

all : lev

clean :
	rm -rf lev_matrix lev_matrix_parallel

lev : lev_matrix.c lev_matrix_parallel.c
	${CC} lev_matrix.c -o lev_matrix
	${CC} lev_matrix_parallel.c -o lev_matrix_parallel -fopenmp

run:
	./lev_matrix
	./lev_matrix_parallel
