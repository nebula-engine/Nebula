#include <neb/core/math/geo/polygon.hpp>

math::geo::polygon::polygon(): triangles_(NULL), nbTriangles_(0)
{
}
math::geo::triangle*	math::geo::polygon::getTriangles()
{
	std::cout << __PRETTY_FUNCTION__ << this << std::endl;
	return triangles_;
}
unsigned int		math::geo::polygon::getNbTriangles()
{
	std::cout << __PRETTY_FUNCTION__ << this << std::endl;
	return nbTriangles_;
}
void			math::geo::polygon::setTriangles(math::geo::triangle* triangles, unsigned int nbTriangles)
{
	triangles_ = triangles;
	nbTriangles_ = nbTriangles;
}

