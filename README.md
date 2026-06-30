# Simple Game Engine

**Version:** *0.0.1 alpha "Just experimenting"*.

## What
A repository I decided to make just for fun to keep software engineering sharp while grinding throu my bachelor's math classes (don't get me wrong, I love Calculus and Linear Algebra, but there isn't a lot of programming in there). Also to try out a few things:
- Post-Modern C, a.k.a C but we use modules (better compile times, no header hell), namespaces (good for organization), default function values (usefull for when the parameter has a commonly used value) and templates (when justifiable, such as data structures). Also STL for prototyping stuff while we don't have our own custom data structures.
- Building a platform layer from scratch (less bloat);
- CPU rendering (because GPU programming is an absolute mess, so it's justifiable if it's not requiered for the current task);
- Data oriented design (SIMD go brrrrr) and compression oriented programming (check sources);
- Creating a simple puzzle game (because I've been playing a lot of those recently).

Please don't use this as an actuall engine, this is just a reference/POC/pet project.

## Building
Clone the repo and enter it with:
- A C++26 compatible compiler (makefile defaults to `g++`);
- GNU Make.

Then for a debug build:
```bash
make -j$(nproc) TARGET=core
```

For a release build:
```bash
make -j$(nproc) MODE=release TARGET=core
```

More build options will be added latter as the project grows in complexity.

A sample config for [Focus Editor](https://github.com/focus-editor/focus) is provided along with the project, only requiering you to copy it to where your focus projects are and setup the absolute path to the root (compiles with F1 and runs with F2).

## References
Check [sources](sources.md).

## Progress
Progress for each version is tracked at [todo](todo.md).

Only the progress tab of the previous version is stored. I don't think a changelog is requiered since it's a hobby project.