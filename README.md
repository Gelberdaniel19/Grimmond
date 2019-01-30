# Grimmond
A roguelite dungeon crawler
Written in C++ with SDL for graphics
## [Preview](https://www.youtube.com/watch?v=cm-_3QPJx-o)

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
  - [x] Wall and player collision handling
  
- [x] Window
  - [x] Empty window
  - [x] Window with level shown
  	- [x] Z depth in render system
  - [x] Camera used
  - [ ] Prettify (NOT IMPORTANT)
  	- [x] Nicer colors
	- [x] Player has nested squares
	- [x] Different size for portals/player?
	- [x] Clouds in background
	- [x] Portals have varied color
	- [ ] Themed levels
	- [x] Fade in to levels
	- [x] Floor labels

- [x] Keyboard control
- [x] Game loop

- [x] Traverse Rooms
- [x] Traverse Levels

- [ ] Enemies
  - [x] Spawn
  - [ ] Aggro
  - [x] Pathfinding
- [ ] Enemy and player health

- [ ] Player projectile ability
- [ ] Player class types

- [ ] Main menu scene
- [ ] Pause menu scene