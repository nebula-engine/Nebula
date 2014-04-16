glutpp

Window and 3D graphics library in c++ using GLUT.

TODO

# Reflections

# Shaddows

# Smoke

# Stenciling

# Fog

# Curved Reflections

# Classes for Rendering Objects

Classes to contain data arrays for positions, normals, texture coordinates. Classes to hold textures. Classes for uniforms and attributes. Find on internet code to parse PLY files.

## Geometry Based Methods

In geometry-based methods, each vertex of a reflected object is transformed by the reflector and the reflected object is then constructed normally using the transformed vertices.

### Explosion map

A sphere surrounds the reflecting surface. The surface oif the sphere is divided up based on which triangle of the reflector reflects that region of space. The surface of the sphere is mapped to the circle. The explosion map is implemented using a texture or frame buffer object. The reflector is rendered with shaders that transform the verticies to the circle. This scene is rendered to a texture or FBO. This object is then used to determine the triangle which reflects each vertex of each reflected object.

### V-Clip variant (concept)

Since the explosion map can be inaccurate base on the radius of the sphere and the distance of the reflected object, a more accurate method is sought. Using something like the V-Clip algorithm, represent the region of space which a triangle reflects as a voronoi region. The V-Clip algorithm would need to be adapted since the face-edge planes are no longer orthogonal to the faces, nor are they necessarily a standard plane. Also, if vertex normals are averaged and not per-face, the edge regions will be non-existant.



