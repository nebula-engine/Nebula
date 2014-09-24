#include <cstdlib>
#include <cassert>

#include <neb/core/math/geo/polygon.hpp>
#include <neb/core/math/geo/polyhedron.hh>

math::geo::polyhedron::polyhedron(): polygons_(NULL), nbPolys_(0)
{
}
unsigned int		math::geo::polyhedron::getNbTriangles()
{
	std::cout << __PRETTY_FUNCTION__ << this << std::endl;
	assert(polygons_);
	
	unsigned int n = 0;

	for(unsigned int i = 0; i < nbPolys_; i++)
	{
		n += polygons_[i].getNbTriangles();
	}

	return n;
}
math::geo::triangle*		math::geo::polyhedron::getTriangles()
{
	
	std::cout << __PRETTY_FUNCTION__ << this << std::endl;
	assert(polygons_);
	
	unsigned int nbTriangles = getNbTriangles();
	
	assert(nbTriangles);

	triangle* triangles = new triangle[nbTriangles];
	

	unsigned int c = 0;
	for(unsigned int i = 0; i < nbPolys_; i++)
	{
		triangle* t = polygons_[i].getTriangles();
		assert(t);

		for(unsigned int j = 0; j < polygons_[i].getNbTriangles(); j++)
		{
			triangles[c++] = t[j];
		}
	}
	
	return triangles;
}

