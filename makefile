CC=gcc
out=sem_fork_e
main=sem_fork.c

$(out): sem_fork.o sem_functions.o
	$(CC) -o sem_fork_e sem_fork.o sem_functions.o
sem_functions.o: sem_functions.c
	$(CC) -o sem_functions.o -c sem_functions.c
sem_fork.o: $(main)
	$(CC) -o sem_fork.o -c  $(main)

clean:
	rm -rf *.o sem_fork_e
