# Grimmond
A roguelite dungeon crawler
Written in C++ with SDL for graphics

## TODO (Logic)
- [x] Working entity component system
- [x] Transform Component
- [ ] Hitbox Component
- [ ] Procedural room generation algorithm (Not under EntityManager, but own class?)
- [ ] Procedural level:
  - [ ] Many rooms linked by portals
  - [ ] Player spawns randomly, stairs to next level spawns randomly
  - [ ] A path to the stairs from the player is created with portals
  - [ ] All unlinked rooms are connected to the main link somehow
  - [ ] If the amount of links is less than the amount of rooms+1, add more
- [ ] Collision
- [ ] PlayerStats Component
- [ ] Camera
- [ ] Game loop
- [ ] KeyboardControl Component
- [ ] Sprite Component
- [ ] Player can traverse portals 
- [ ] EnemyStats Component
- [ ] Enemy pathfinding
- [ ] Player projectile ability
- [ ] Player can go to next level
- [ ] Player classes
- [ ] Main menu scene
- [ ] Pause menu scene

## TODO (Graphics)
- [ ] Create initial sprites
  - [x] Player
  - [x] Level 1 ground
  - [x] Level 1 walls (with connected textures)
  - [ ] Basic enemy
  - [ ] Projectile
- [ ] Complete Render methods in entities
- [ ] Background (class?) which renders moving rectangles like clouds-ish
- [ ] HUD (health, mana, etc)
- [ ] Connected textures for the walls
- [ ] Animations
- [ ] More sprites
  - [ ] Other player classes
  - [ ] Many more types of enemies
  - [ ] Different ground and wall textures for higher levels
  - [ ] More TBD