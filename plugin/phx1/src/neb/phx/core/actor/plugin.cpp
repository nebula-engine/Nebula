#include <neb/fnd/plug/phx/core/actor/util/decl.hpp>

#include <neb/phx/core/actor/rigiddynamic/base.hpp>
#include <neb/phx/core/actor/rigidstatic/base.hpp>

namespace NS0 = neb::fnd::plug::phx::core::actor;
namespace NS1 = neb::phx::core::actor;

typedef NS0::Base T0;

typedef NS1::rigiddynamic::base RD;
typedef NS1::rigidstatic::base RS;

extern "C" T0*	actor_create(int i)
{
	switch(i) {
	case NS0::type::RIGIDDYNAMIC:
		return new RD;
	case NS0::type::RIGIDSTATIC:
		return new RS;
	default:
		abort();
	}
	return 0;
}
extern "C" void	actor_destroy(T0* t)
{
	delete t;
}

