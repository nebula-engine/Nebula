#ifndef NEB_PHX_TMP_CHILD_HPP
#define NEB_PHX_TMP_CHILD_HPP

#include <neb/fnd/tmp/Child.hpp>

#include <neb/phx/app/util/decl.hpp>

namespace neb { namespace phx { namespace tmp {
	template<class T> class Child:
		virtual public neb::fnd::tmp::Child<T>
	{
		public:
			neb::phx::app::base * const	get_phx_app()
			{
				auto a = neb::fnd::tmp::Child<T>::get_fnd_app();
				auto p = dynamic_cast<neb::phx::app::base*>(a);
				assert(p);
				return p;
			}
	};
}}}

#endif
