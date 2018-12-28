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
  
- [ ] Window
  - [x] Empty window
  - [x] Window with level shown
  - [ ] Camera used
  
- [x] Keyboard control
- [x] Game loop

- [ ] Clouds in background
  - [x] Z depth in render system

- [ ] Traverse Rooms
- [ ] Traverse Levels

- [ ] Player stats
- [ ] Enemy stats
- [ ] Enemy pathfinding

- [ ] Player projectile ability
- [ ] Player class types

- [ ] Main menu scene
- [ ] Pause menu scene