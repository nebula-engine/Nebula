#include <neb/fnd/plug/phx/core/scene/util/decl.hpp>

#include <neb/phx/core/scene/base.hpp>

namespace NS0 = neb::fnd::plug::phx::core::scene;
namespace NS1 = neb::phx::core::scene;

typedef NS0::Base T0;

typedef NS1::base T;

extern "C" T0*	scene_create(int i)
{
	return new T;
	
	return 0;
}
extern "C" void	scene_destroy(T0* t)
{
	delete t;
}

