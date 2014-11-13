#include <neb/gfx/util/log.hpp>
#include <neb/gfx/window/util/Parent.hh>

void		neb::gfx::window::util::parent::render() {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	auto lamb = [&] (pointer p) {
		p->render();
	};

	map_.for_each(lamb);

}

