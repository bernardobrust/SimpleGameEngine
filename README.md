# Simple Game Engine

**Version:** *0.0.1 pre-alpha "Just experimenting"*.

## What
A repository I decided to make just for fun to keep software engineering sharp while grinding throu my bachelor's math classes (don't get me wrong, I love Calculus and Linear Algebra, but there isn't a lot of programming in there). Also to try out a few things:
- Post-Modern C, a.k.a C++ but we only use modules, namespaces, default function values and templates when justifiable. (Also STL for prototyping stuff while we don't have our own custom data structures).
- Building a platform layer from scratch;
- CPU rendering;
- Data oriented design;
- Creating a simple puzzle game.

Please don't use this as an actuall engine, this is just a reference.

## Building
Clone the repo and enter it with:
- A C++26 compatible compiler (`g++, clang++, etc.`);
- GNU Make;

Then for a debug build:
```bash
make -j$(nproc) TARGET=core
```

For a release build:
```bash
make -j$(nproc) MODE=release TARGET=core
```

More build options will be added latter as the project grows in complexity.

## References
Check [sources](sources.md)

## Progress
Progress for each version is tracked at [todo](todo.md)