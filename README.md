Nebula
======

3D Game Engine in C++

## Components

[core](http://github.com/chuck1/Nebula-Core)

## Dependencies

[glfw](http://github.com/glfw/glfw)
[glm](http://github.com/g-truc/glm)

## Installation

    git clone github.com/chuck1/Nebula.git
    cd Nebula
    git submodule init
    git submodule update
    mkdir Debug
    cd Debug
    cmake ..
    make install

## Networking

### basic server-client model

Networking requires determining if the core objects are local or remote.
Local means they are on the server machine, remote means they are on a client machine.
Local scenes simulate physics and send pose data to clients via the actor's v\_set\_pose\_data.
Object determine if they are local or remote via the \_M\_network\_object pointer.

## Plugins

neb::fnd::plug classes are used to implement special functionality.
They are the children of corresponding neb::fnd classes.
They are used when the functionality is optional but the underlying structure is still needed (e.g. scenes, actors).

Plugin classes

Full Rebuild

real	7m33.772s
user	26m25.272s
sys	1m46.803s


