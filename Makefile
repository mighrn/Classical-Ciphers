all:	cipher

cipher:	cipher.o
	g++ cipher.o -o cipher

cipher.o:	cipher.cpp
	g++ -g -c cipher.cpp


clean:
	rm -rf *.o cipher
