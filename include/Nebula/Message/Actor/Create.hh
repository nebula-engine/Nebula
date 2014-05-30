#ifndef __GLUTPP_NETWORK_ACTOR_CREATE_H__
#define __GLUTPP_NETWORK_ACTOR_CREATE_H__

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <Nebula/config.hh>
#include <Nebula/App/Base.hh>
#include <Nebula/Message/Actor/Event/Base.hh>
#include <Nebula/Actor/Base.hh>

namespace Neb {
	namespace Message {
		namespace Actor {
			struct Create {
				public:
					void				load(Neb::Actor::Base_s actor);

					template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
						ar & parent_i_;
						ar & i_;
						ar & wrapper_;
					}
				public:
					Neb::Util::index_type				parent_i_;
					/** @brief Address.
					 * address at which the new actor object will be stored
					 */
					Neb::Util::index_type				i_;
					/** @brief Wrapper.
					 * wrapper to create the actor object
					 */
					Neb::WrapperTyped<Neb::Actor::Base>		wrapper_;
			};
		}
	}
}





#endif


