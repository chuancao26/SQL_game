test: main.o
	g++ -o test main.o -L/usr/local/SFML-2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system
main.o: main.cpp
	g++ -c main.cpp -I/usr/local/SFML-2.6.1/include
