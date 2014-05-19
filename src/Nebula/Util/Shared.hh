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
				typedef std::shared_ptr<Neb::Util::Shared>	shared;
				typedef std::weak_ptr<Neb::Util::Shared>	weak;
				
				Registry(): next_(0) {
				}
				void					reg(shared s);
				void					reg(shared s, Neb::Util::index_type);
				shared					get(Neb::Util::index_type i);
			private:
				std::map<index_type, weak>		map_;
				Neb::Util::index_type			next_;

		};
		/** @brief %Shared.
		 * avoid multiple enabled_shared_from_this bases
		 */
		class Shared:
			virtual public std::enable_shared_from_this<Shared>
		{
			public:
				Shared();
				Shared(Neb::Util::index_type);
				virtual ~Shared() {}

			public:
				static Registry					registry_;
				Neb::Util::index_type				i_;
		};
	}
}

#endif

