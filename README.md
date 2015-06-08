Nebula
======

3D Game Engine in C++

[videos](https://www.youtube.com/playlist?list=PLjZBaNxFBCGRns2c8nB6sJDiGlmUCxrQA)

## Features

- 3D rendering using glfw/OpenGL
- 3D physics simulations using Nvidia PhysX
- python-powered scripting and control using in-game terminal and script file loading
- network multiplayer support is under construction

## Components

- [core](http://github.com/nebula-engine/Nebula-Core) - abstract classes which define engine structure
- [physx](http://github.com/nebula-engine/Nebula-Core) - physics component
- [gfx](http://github.com/nebula-engine/Nebula-Core) - grpahics component
- [python](http://github.com/nebula-engine/Nebula-Core) - python component
- [network](http://github.com/nebula-engine/Nebula-Core) - networking component

## Dependencies

[glfw](http://github.com/glfw/glfw)
[glm](http://github.com/g-truc/glm)

## Installation

this might be out-of-date, need to verify

    git clone github.com/chuck1/Nebula.git
    cd Nebula
    git submodule init
    git submodule update
    mkdir Debug
    cd Debug
    cmake ..
    make install

## Networking

### Basic Server-Client Model

- Networking requires determining if the core objects are local or remote.
- Local means they are on the server machine, remote means they are on a client machine.
- Local scenes simulate physics and send pose data to clients via the actor's v\_set\_pose\_data.
- Objects determine if they are local or remote via the \_M\_network\_object pointer.

## Plugins

- neb::fnd::plug classes are used to implement special functionality.
- They are the children of corresponding neb::fnd classes.
- They are used when the functionality is optional but the underlying structure is still needed (e.g. scenes, actors).

## Server-Client Connection Process

- Issue: need to assign unique index\_process to each process
- Solution: assume all processes connected by a given network have
registered with the same RegistryProcess server.
- By default, a process will have an invalid index\_process.

## Temp Notes

client process_managed isnt being registered!

## Boost

theory about Boost Asio: only one async callback will run at a time.
So, if an async callback blocks, no other async calls will complete until the blockage clears









