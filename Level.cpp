#include "Level.hpp"

Room* Level::GetDestRoom(Room* src, int portalnum)
{
	for (Room* room : rooms) {
		if (src == room) continue;

		std::vector<std::vector<int>> tiles = room->GetTiles();
		for (int row = 0; row < tiles.size(); row++)
			for (int col = 0; col < tiles[0].size(); col++)
				if (tiles[row][col] == portalnum)
					return room;
	}

	return nullptr;
}

Level::Level(World* w)
{
	world = w;

	// Seed the rng
	rng.seed(std::random_device()());

	// Make 6-10 rooms
	std::uniform_int_distribution<std::mt19937::result_type> randRoomCount(6, 10);
	int roomCount = randRoomCount(rng);
	std::uniform_int_distribution<std::mt19937::result_type> randRoomPicker(0, roomCount-1);
	for (int i = 0; i < roomCount; i++)
		rooms.emplace_back(new Room(this, MAP_WIDTH, MAP_HEIGHT));

	// Put player and stairs in random different rooms
	int playerRoom = randRoomPicker(rng);
	int stairsRoom = randRoomPicker(rng);
	while (stairsRoom == playerRoom)
		stairsRoom = randRoomPicker(rng);
	rooms[playerRoom]->InsertTileOnGround(PLAYER);
	rooms[stairsRoom]->InsertTileOnGround(STAIR);
	activeRoom = rooms[playerRoom];

	// Generate linked portals to make a path to the stairs
	int portalnum = 100;
	int prevRoom = playerRoom;
	do {
		// Pick a random new room
		int randRoom = randRoomPicker(rng);
		while (rooms[randRoom]->HasPortal() || randRoom == prevRoom)
			randRoom = randRoomPicker(rng);

		// Link them with a portal
		rooms[prevRoom]->InsertTileOnGround(portalnum);
		rooms[randRoom]->InsertTileOnGround(portalnum);
		portalnum++;
		prevRoom = randRoom;
	} while (prevRoom != stairsRoom);

	// Ensure every room is linked to the rooms on the path to stairs
	for (int i = 0; i < roomCount; i++) {
		if (!rooms[i]->HasPortal()) {
			// Pick random room until one has a portal
			int randRoom = randRoomPicker(rng);
			while (!rooms[randRoom]->HasPortal())
				randRoom = randRoomPicker(rng);

			// Link the rooms
			rooms[i]->InsertTileOnGround(portalnum);
			rooms[randRoom]->InsertTileOnGround(portalnum);
			portalnum++;
		}
	}

	// If the number of links is less than roomCount + 1, keep adding random links
	while (portalnum - 100 < roomCount + 1) {
		// Pick two random, DIFFERENT rooms
		int room1 = randRoomPicker(rng);
		int room2 = randRoomPicker(rng);
		while (room2 == room1)
			room2 = randRoomPicker(rng);

		// Link em
		rooms[room1]->InsertTileOnGround(portalnum);
		rooms[room2]->InsertTileOnGround(portalnum);
		portalnum++;
	}
}

void Level::Start()
{
	std::cout << "Entering Level" << std::endl;
	while (!complete && running) {
		std::cout << "Entering Room" << std::endl;
		activeRoom->Play();
		std::cout << "Exiting Room" << std::endl;
	}
	std::cout << "Exiting Level" << std::endl;
}

Level::~Level()
{
	for (Room* r : rooms)
		delete r;
}
