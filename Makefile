temp:
	g++ -c Room.cpp Level.cpp driver.cpp globals.cpp
	g++ -c engine/ECS.cpp -o engine/ECS.o
	g++ Room.o Level.o driver.o globals.o engine/ECS.o -o out -lSDL2 -lSDL2_ttf
	rm *.o
	rm engine/*.o
