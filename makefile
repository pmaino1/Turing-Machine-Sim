
all: maino_p1

maino_p1: maino_p1.cpp
	g++ -g -Wall -std=c++14 maino_p1.cpp -o maino_p1

clean:
	rm -rf *.o maino_p1
