# Grimmond
A roguelite dungeon crawler
Written in C++ with SDL for graphics

## TODO (Logic)
- [x] Working entity component system
- [x] Transform Component
- [x] Physics Component and System
- [x] Render Component and System

- [x] Procedural level:
  - [x] Generation algorithm for Rooms
  - [x] Many rooms linked by portals
  - [x] Player spawns randomly, stairs to next level spawns randomly
  - [x] A path to the stairs from the player is created with portals
  - [x] All unlinked rooms are connected to the main link somehow
  - [x] If the amount of links is less than the amount of rooms+1, add more
  
- [x] Collision
  - [x] Collision algorithm
  - [x] Send collision events to colliding entities
  - [x] Wall and player collision handling
  
- [x] Window
  - [x] Empty window
  - [x] Window with level shown
  	- [x] Z depth in render system
  - [x] Camera used
  - [ ] Prettify (NOT IMPORTANT)
  	- [ ] Nicer colors
	- [ ] Player has nested squares
	- [ ] Different size for portals/player?
	- [ ] Clouds in background
	- [x] Portals have varied color
	- [ ] Themed levels
	- [ ] Fade in to levels

- [x] Keyboard control
- [x] Game loop

- [x] Traverse Rooms
- [ ] Traverse Levels

- [ ] Player stats
- [ ] Enemy stats
- [ ] Enemy pathfinding

- [ ] Player projectile ability
- [ ] Player class types

- [ ] Main menu scene
- [ ] Pause menu scene