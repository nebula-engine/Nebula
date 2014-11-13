#ifndef NEBULA_STD_WRAPPER_HPP
#define NEBULA_STD_WRAPPER_HPP

#include <gal/stl//wrapper.hpp>

#include <gal/etc/timestep.hpp>

#include <neb/core/itf/shared.hpp>

namespace neb {
	namespace stl {
		class wrapper: virtual public gal::stl::wrapper<neb::itf::shared> {
			public:
				wrapper();
				wrapper(std::shared_ptr<neb::itf::shared> s);
				virtual void		init();
				virtual void		release();
				virtual void		step(gal::etc::timestep const & ts);
		};
	}
}
#endif
