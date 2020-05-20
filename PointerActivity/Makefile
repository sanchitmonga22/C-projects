default: test_pointers

test_pointers: read_data.o main.o
	gcc -g -o test_pointers read_data.o main.o

read_data.o: read_data.c read_data.h
	gcc -g -Wall -c read_data.c

main.o: main.c read_data.h
	gcc -g -Wall -c main.c

clean:
	-rm -f read_data.o
	-rm -f main.o
	-rm -f test_pointers
