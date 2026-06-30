## Todo list for version 0.0.1 beta
**GOAL:** Working GNU + Linux X11 platform layer (windowing only for now)

We start with X11 as it's the most used, most Wayland users (like me) have XWayland to run X based aplications. I'll use `lX11` for this.

However, Wayland is way better to develop and use than X11, so I'll be way more carefull with that one. I'll like do the wayland layer from scratch.

### General
- [x] Update docs pre-work
- [ ] Modularized support for platform layer
- [ ] Build system chooses module use based on OS and WINDOWING compilation variables
- [ ] Update docs post-work

### Core Engine
- [ ] Open a X11 window
- [ ] Draw something to it

### Platform Layer
- [ ] Choose lib based on compilation target

Provide a platform-agnostic interface for the rest of the engine to use:
- [ ] Generalized interface module with only signatures
- [ ] Specialized X11 module implements the interface if the macro `PLATFORM_GNU_LINUX_X11` is defined (passed via `-DPLATFORM_GNU_LINUX_X11` in the makefile)

The general module should provide (for now):
- [ ] A `PlatformState` struct, containing a `void *` internal state (depends on the layer, templating here makes no sense)
- [ ] `platform_init`: self-explanatory
- [ ] `platform_update`: for now we just pool events, latter we will give it a buffer to blit for example
- [ ] `platform_shutdown`: self-explanatory

***

# Previous version

## Todo list for version 0.0.1 alpha
**GOAL:** A working dynamic array data structure

### General
- [x] Update docs pre-work
- [x] Modularized support for data structures
- [x] Add gnu formating
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