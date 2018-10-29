all: main.o
    gcc -o men main.o

main.o: main.c
    gcc -c main.c
clean:
    rm *.o
run:
    ./men