#ifndef NEBULA_STD_WRAPPER_HPP
#define NEBULA_STD_WRAPPER_HPP

#include <Galaxy-Standard/wrapper.hpp>

#include <Nebula/core/TimeStep.hpp>
#include <Nebula/util/shared.hpp>

namespace neb {
	namespace std {
		class wrapper: virtual public gal::std::wrapper<neb::std::shared> {
			public:
				wrapper();
				wrapper(sp::shared_ptr<neb::std::shared> s);
				virtual void		init();
				virtual void		release();
				virtual void		step(neb::core::TimeStep const & ts);
		};
	}
}
#endif
