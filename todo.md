## Todo list for version 0.0.1 alpha
**GOAL:** A working dynamic array data structure

### General
- [x] Update docs pre-work
- [x] Modularized support for data structures
- [x] Add gnu foirmatting
- [x] Update docs post-work

### Core Engine
- [x] Change `EntityRegistry` to use `engine::ds::dyn_arr`

### Data Structures
- [x] Create a `engine::ds::dyn_arr` module, should be templated (justified)

Funtions:
- [x] init given a size, **DO NOT ZERO MEMORY ON ALLOCATION**, we assume the caller will assign latter. Because of this, we only support trivial datatypes, since this is a Data Oriented project this is fine. Moreover, we can document this with `static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");` to check at compile time this assumption is correct. Metadata is stored by the struct.
- [x] push with an implicit re-sacale parameter (2, can be any float > 1). **O(1) amortized**
- [x] pop with an implicit de-scale parameter (false) that reduces the size of the vector after deleting if it falls bellow a threshold (2). **O(1) amortized**
- [x] insert, push but can specify a specific position. **O(n)**
- [x] remove (delete is taken as a keyword), pop but can specify a specific position. **O(n)**
- [x] length, the amount of used slots
- [x] size, the total memory used by the data structure, with implicit header parameter (false) that adds the shadowed metadata to the size

Debug Utility:
- [x] print_data prints all elements
- [x] print_metadata prints used/sza

### Problems for next versions
- Of course, check that the data structure works correctly and efficienlty in the long run
- We still have to do with ensuring access to the entity registry is controlled during debug builds

***

# Previous version

## Todo list for version 0.0.1 pre-alpha
**GOAL:** have a working data-oriented pipeline

### General
- [x] Update this TODO list with a more concrete plan (recursive?)
- [x] Improve readme
- [x] Setup a git repo
- [x] Send to github

### Build System
- [x] Just support compiling a core for now with a module system

### Core Engine
Create basic data components: (SoA)
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

### Problems for next versions
- Somehow ensure all vector in EntityRegistry have the same size after adding/deleting elements
- Benchmarking `std::vector` vs my own dynamic arrays (I can probably pull some tricks to make it faster).