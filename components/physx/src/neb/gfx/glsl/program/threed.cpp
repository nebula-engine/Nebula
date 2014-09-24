#include <neb/gfx/util/log.hpp>
#include <neb/gfx/glsl/program/threed.hpp>

void		neb::gfx::glsl::program::threed::init() {
	
	auto self = std::dynamic_pointer_cast<neb::gfx::glsl::program::threed>(shared_from_this());

	
	neb::gfx::glsl::program::base::init();
	
	//light_locations_.init(self);

}

