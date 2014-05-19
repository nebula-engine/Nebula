#ifndef __GRU_SHARED_HPP__
#define __GRU_SHARED_HPP__

#include <memory>
#include <map>

#include <Nebula/Types.hh>

namespace Neb {
	namespace Util {
		class Shared;
		class Registry {
			public:
				Registry(): next_(0) {
				}
				void						reg(std::shared_ptr<Neb::Util::Shared> s);
				std::shared_ptr<Neb::Util::Shared>		get(Neb::Util::index_type i);
			private:
				std::map<index_type, std::weak_ptr<Neb::Util::Shared> >		map_;
				Neb::Util::index_type						next_;

		};
		/** @brief %Shared.
		 * avoid multiple enabled_shared_from_this bases
		 */
		class Shared:
			virtual public std::enable_shared_from_this<Shared>
		{
			public:
				Shared();
				virtual ~Shared() {}

			public:
				static Registry					registry_;
				Neb::Util::index_type				i_;
		};
	}
}

#endif

