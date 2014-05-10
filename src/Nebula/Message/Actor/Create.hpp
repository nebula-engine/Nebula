#ifndef __GLUTPP_NETWORK_ACTOR_CREATE_H__
#define __GLUTPP_NETWORK_ACTOR_CREATE_H__

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <gru/config.hpp>
#include <gru/master.hpp>
#include <gru/scene/desc.hpp>
#include <gru/actor/desc.hpp>
#include <gru/actor/addr.hpp>
#include <gru/actor/event.hpp>
#include <gru/actor/raw_factory.hpp>
#include <gru/actor/actor.hpp>

namespace Neb {
	namespace Message {
		namespace Actor {
			struct Create {
				void				load(Neb::actor::actor_w actor);

				template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
					ar & addr_;
					ar & desc_;
				}
				
				/** @brief Address.
				 * address at which the new actor object will be stored
				 */
				Neb::Actor::addr				addr_;
				/** @brief Wrapper.
				 * wrapper to create the actor object
				 */
				Neb::WrapperTyped<Neb::Actor::Base>		wrapper_;
			};
		}
	}
}





#endif


