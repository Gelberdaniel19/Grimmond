temp:
	g++ -c Room.cpp Level.cpp driver.cpp
	g++ Room.o Level.o driver.o -o out
	rm *.o
