#include <neb/fnd/plug/phx/core/shape/util/decl.hpp>

#include <neb/phx/core/shape/box.hpp>

namespace NS0 = neb::fnd::plug::phx::core::shape;
namespace NS1 = neb::phx::core::shape;

typedef NS0::Base T0;

typedef neb::phx::core::shape::base B;
typedef neb::phx::core::shape::box C;

extern "C" T0*	shape_create(int i)
{
	switch(i) {
	case NS0::type::CUBOID:
		return new C;
/*	case NS0::type::BASE:
		return new B;*/
	default:
		abort();
	}
	
	return 0;
}
extern "C" void	shape_destroy(T0* t)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	delete t;
}

