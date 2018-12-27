temp:
	g++ -c Room.cpp Level.cpp driver.cpp
	g++ -c engine/ECS.cpp -o engine/ECS.o
	g++ Room.o Level.o driver.o engine/ECS.o -o out
	rm *.o
	rm engine/*.o
