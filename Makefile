temp:
	g++ -c *.cpp
	g++ *.o -lSDL2 -lSDL2_ttf
	rm *.o
