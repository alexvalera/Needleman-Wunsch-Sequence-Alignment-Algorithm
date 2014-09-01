all: Needleman-Wunsch 

Needleman-Wunsch: Needleman-Wunsch.o 
		g++ Needleman-Wunsch.o -o Needleman-Wunsch

Needleman-Wunsch.o: Needleman-Wunsch.cpp
		g++ -c Needleman-Wunsch.cpp
		
clean:

	rm -rf *o Needleman-Wunsch 