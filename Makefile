all : index

index : proj1b.o
	g++ -o index -g proj1b.o

proj1.o : proj1b.cpp
	g++ -Wall -c -g proj1b.cpp



clean :
	rm *.o
	rm index
