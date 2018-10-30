#inlude "Level.hpp"

Level::Level()
{
	// TODO Generate random number 6-10
	int roomCount = 8;
	for (int i = 0; i < roomCount; i++)
		rooms[i] = new Room();

	// Put player and stairs in random room
	int playerRoom = 0;
	int stairsRoom = 8;
	rooms[playerRoom]->InsertTileOnGround(PLAYER);
	rooms[stairsRoom]->InsertTileOnGround(STAIR);

	// Generate linked portals to make a path to the stair
	int portalnum = 100;
	int prevRoom = playerRoom;
	do {
		// TODO Pick random room
		int randRoom = 1;
		rooms[prevRoom]->InsertTileOnGround(portalnum);
		rooms[randRoom]->InsertTileOnGround(portalnum);

		prevRoom = randRoom;
		portalnum++;
		if (portalnum > 200)
			break;
	} while (!rooms[randRoom]->HasPortal());

	// Ensure every room is linked to the rooms on the path to stair
	for (Room* r : rooms) {
		if (!r->HasPortal()) {
			// TODO Pick random room until one has a portal
			int randRoom;
			do {
				randRoom = 1;
			} while (!rooms[randRoom]->HasPortal());

			// Link the rooms
			r->InsertTileOnGround(portalnum);
			rooms[randRoom]->InsertTileOnGround(portalnum);
			portalnum++;
		}
	}

	// If the number of links is less than roomCount + 1, keep adding random links
	while (portalnum - 100 < roomCount + 1) {
		// Pick two random, DIFFERENT rooms
		int room1 = 1;
		int room2;
		do {
			room2 = 2;
		} while (room1 == room2);

		// Link em
		rooms[room1]->InsertTileOnGround(portalnum);
		rooms[room2]->InsertTileOnGround(portalnum);
		portalnum++;
	}
}

Level::~Level()
{
	for (int i = 0; i < 10; i++)
		delete rooms[i];
}
