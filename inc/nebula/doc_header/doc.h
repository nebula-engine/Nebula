


/** \mainpage
*
* \section intro Introduction
*
* \subsection proj The Project
*
* Nebula is a 3D game engine written in c++. The goal of the project is a develop a versatile and cross-platform SDK.
* The SDK is first being developed for Windows and Linux systems with OpenGL for 3D rendering. PhysX by NVidia is used for physics.
* The goal for future versions is to support additional platforms such as XBOX, PS3, and Android as well as other rendering API's.
*
* \subsection author The Author
*
* The sole author is Charles Rymal.
*
* \subsection TODO TODO
* - Get Windows window and rendering working
* - Create animation hierarchy system
* - Create rendering system with arbitarary meshes for any item, texture, lights, etc.
* - Download and learn 3D model editor/ texture editor
* - Create random maze generator at high level
* - Change all float and float-dependent to typedef that can be switched easily from float to double
* - Create Event communication system
* - Create Maze Game
* - Create game logic tools
* - Create scripting
*     - For use by game designer
* - Create console
*     - Create text rendering
* - Create generalized player programmability
*     - Implement using multiple scripting languages
*         - Assembly
*         - C
* 
* \section audio Audio
Possible SDKs
- OpenAL
- FMOD









* \section outline Outline of Things Not Added
* - Physics
*     - Physx
*         - particle
*         - cloth
*     - APEX
*         - destruction
*         - turbulence
* - Animation
*     - Top level information about an animation or animation object.
*     - Must potentially work with Actor, Physics, Render,...
* - Audio
* - Cinematics
* - Render
*     - HUD
* - Level
* - Scripting
*     - Defined in context of other systems such as AI, Level, Render,...
* - Tools
*     - Model Editor
*         - external tool for creation of characters, weapons, vehciles, etc.
*     - Level Editor
*         - terrain (FLOATistic shape and texture)
*         - terrain algorithm editor
*         - events
* - Camera Angles
*     - Relative to various axes
*         - Actor
*         - Actor shape
*         - CO_SC_AD_Scene
*     - View behavior
*         - orientation
*         - translation
* - Memory Zones
*     - physics data
*     - render data
*     - content data
*     - abstract data not used directly by physics or render
*         - example
*             - health
*             - objectives







* 
* \page galsim Celestial Body Simulation
* For celestial bodies, each body has an aabb.
* The size of the aabb depends on the body's mass and velcoity.
* If two bodies have overlapping aabb, their motion is solved by kinetics (force, velocity).
* 
* If the aabb overlaps nothing, the body travels in a straight line or depends only on its own forces (thrusters).
* 








* \page gameideas Game Ideas
* - For rts-style games, have a single resource type. Each unit of resource has a value in a continuous range (like electromagnetic spectrum). Resources can be converted to different values at a cost (conversion efficiency). Different purchasable things could require different combinations of values. This could work well with evolutionary algorithm-based populations which could evolve to feed on different values.
* - Steal idea from 0x10c and have fully programmable 16-bit computer to control various things (like a spaceship). Or perhaps a more advanced computer with a c-like programming language. This would be easier for programming things like launch and re-rentry sequences for spacecraft.
* 
* 
* 
* 
* 
* 




*/

