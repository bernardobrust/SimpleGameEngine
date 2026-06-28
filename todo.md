# Todo list for version 0.0.1 pre-alpha
**GOAL:** have a working data-oriented pipeline

### General
- [ ] Update this TODO list with a more concrete plan (recursive?)
- [x] Improve readme
- [x] Setup a git repo
- [ ] Send to github

### Build system
- [x] Just support compiling a core for now with a module system

### Core Engine
Create basic data components:
- [x] Positions (floats)
- [x] Sprites (just ints for now for testing)
- [x] Entity types (enum with, player, enemy, etc...)

Update functions:
- [x] Update positions

Render functions:
- [x] For now just print something like "Rendered enemy X with sprite Y"

Create a pipeline to render and update entities:
- [x] Call updates and renders on all entities

Access and update:
- [x] Access to specific entity by id
- [x] Altering data of a specific entity by it's id

### Data Structures
Use STL for now, it's reasonably efficient for these simple things, but latter we'll likely require some more specialized containers.
