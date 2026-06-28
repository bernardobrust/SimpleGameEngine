# Todo list for version 0.0.1 pre-alpha
**GOAL:** have a working data-oriented pipeline

### General
- [ ] Update this TODO list with a more concrete plan (recursive?)
- [x] Improve readme
- [x] Setup a git repo
- [ ] Send to github

### Build system
- [ ] Just support compiling a core for now with a module system

### Core Engine
Create basic data components:
- [ ] Positions (floats)
- [ ] Sprites (just it's for now for testing)
- [ ] Entity types (enum with, player, enemy, etc...)

Update functions:
- [ ] Update positions

Render functions:
- [ ] For now just print something like "Rendered enemy X with sprite Y"

Create a pipeline to render and update entities:
- [ ] Call updates and renders on all entities

### Data Structures
Use STL for now, it's reasonably efficient for these simple things, but latter we'll likely require some more specialized containers.
