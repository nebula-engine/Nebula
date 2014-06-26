#ifndef NEBULA_LIGHT_SPOT_HH
#define NEBULA_LIGHT_SPOT_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#include <galaxy/flag.hpp>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <neb/config.hh>
#include <neb/util/decl.hpp>
#include <neb/util/shared.hpp>

#include <neb/math/Serialization/GLM.hpp>

#include <neb/core/light/util/Flag.hh>
#include <neb/core/light/util/Types.hh>

#include <neb/gfx/texture.hh>
#include <neb/core/light/base.hpp>


//#include <math/color.hpp>

namespace neb { namespace gfx { namespace core { namespace light {

	class directional: virtual public neb::gfx::core::light::base {
		public:
	};


}}}}

#endif
