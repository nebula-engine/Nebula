#ifndef NEBULA_GFX_ENVIRON_UTIL_CAST_HPP
#define NEBULA_GFX_ENVIRON_UTIL_CAST_HPP

#include <neb/util/shared.hpp>
#include <neb/gfx/util/decl.hpp>

namespace neb { namespace gfx { namespace environ { namespace util {

	class cast:
		virtual public neb::std::shared
	{
		public:
			sp::shared_ptr<neb::gfx::environ::two>		isEnvironTwo();
			sp::shared_ptr<neb::gfx::environ::three>	isEnvironThree();
	};

}}}}

#endif
