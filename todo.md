## Todo list for version 0.0.1 beta p2
**GOAL:** Global map of pressed keys (a.k.a input)

Of course we need to know what keys are being pressed to make a game, we'll do so via a global boolean array that tracks what keys are pressed at the moment

### General
- [x] Update docs pre-work
- [ ] Update docs post-work

### Core Engine
Provide a global boolean array of pressed keys:
- [ ] Keycode = index in the array
- [ ] Provide function `engine::is_key_pressed` that checks in the array
- [ ] Test by rendering the last 3 keys pressed by the user and quit on pressing <esc>.

### Platform Layer
- [ ] The platform layer implementation should update the global array in the update function.

### Problems for future versions
- Does this handle key holding well? How about scrolling and mouse motion?
- Does this approach scale with a controller?

***

# Previous version

## Todo list for version 0.0.1 beta
**GOAL:** Working GNU + Linux X11 platform layer (windowing only for now)

We start with X11 as it's the most used, most Wayland users (like me) have XWayland to run X based aplications. I'll use `lX11` for this.

However, Wayland is way better to develop and use than X11, so I'll be way more carefull with that one. I'll like do the wayland layer from scratch.

### General
- [x] Update docs pre-work
- [x] Modularized support for platform layer
- [x] Build system chooses module use based on OS and WINDOWING compilation macros
- [x] Update docs post-work

### Core Engine
- [x] Open a X11 window
- [x] Draw something to it

### Platform Layer
- [x] Choose lib based on compilation target

Provide a platform-agnostic interface for the rest of the engine to use:
- [x] Generalized interface module with only declarations
- [x] Specialized X11 module implements the interface if the macro `PLATFORM_GNU_LINUX_X11` is defined (passed via `-DPLATFORM_GNU_LINUX_X11` in the makefile)

The general module should provide (for now):
- [x] A `PlatformState` struct, containing a `void *` internal state (depends on the layer, templating here makes no sense)
- [x] `platform_init`: self-explanatory
- [x] `platform_update`: for now we just pool events, latter we will give it a buffer to blit for example
- [x] `platform_shutdown`: self-explanatory

### Problems for future versions
- We have no delta time nor an fps counter