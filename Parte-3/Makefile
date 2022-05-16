utils.o: utils.cpp utils.h
	g++ utils.cpp -c

marketplace.o: marketplace.cpp marketplace.h utils.o
	g++ marketplace.cpp -c

main: main.cpp marketplace.o utils.o picosha2.h
	g++  main.cpp marketplace.o utils.o -o main

all: main

clean:
	rm main *.o