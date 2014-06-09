#ifndef NEBULA_STD_WRAPPER_HPP
#define NEBULA_STD_WRAPPER_HPP

#include <Galaxy-Standard/wrapper.hpp>

#include <Nebula/Core/TimeStep.hpp>
#include <Nebula/Util/shared.hpp>

namespace neb {
	namespace std {
		class wrapper: virtual public gal::std::wrapper<neb::std::shared> {
			public:
				wrapper(sp::shared_ptr<neb::std::shared> s);
				virtual void		init();
				virtual void		release();
				virtual void		step(Neb::Core::TimeStep const & ts);
		};
	}
}
#endif
