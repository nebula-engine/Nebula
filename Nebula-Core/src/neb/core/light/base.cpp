
#include <neb/core/light/base.hpp>

neb::core::light::base::base(sp::shared_ptr<neb::core::light::util::parent> parent):
	parent_(parent),
	pos_(vec4(0.0, 0.0, 0.0, 1.0))
{}





