#include <gal/log/log.hpp>

#include <neb/debug.hh>
#include <neb/gfx/core/light/base.hpp>
#include <neb/gfx/core/light/util/parent.hpp>

void			neb::gfx::core::light::util::parent::load_lights(neb::core::light::util::count & light_count, neb::core::pose const & pose) {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core shape", debug) << __PRETTY_FUNCTION__;
	

	auto lambda_light = [&] (map_type::iterator<0> it) {

		auto light = sp::dynamic_pointer_cast<neb::gfx::core::light::base>(it->ptr_);
		assert(light);

		//if(i == neb::core::light::light_max) return L::map_type::BREAK;
		
		light->load(light_count, pose);
		
		return map_type::CONTINUE;
	};

	map_.for_each<0>(lambda_light);

}

