#ifndef __GLUTPP_NETWORK_ACTOR_UPDATE_HPP__
#define __GLUTPP_NETWORK_ACTOR_UPDATE_HPP__

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <gru/config.hpp> // gru/config.hpp.in
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
			struct Update: Neb::Message::Base {
				
				Update(): count_(0) {}
				
				/** @brief Default load/save operator.
				 * All other types are simply passed to the archive
				 */
				template<typename T> Update&		operator&(T const & t) {
					msg_->ar_ & t;
				}
				
				int				count_;
				std::stringstream::pos_type	pos_count_;
				
			};
			struct OUpdate: Update {
				/** @brief Save %Actor. */
				Update&		operator<<(Neb::Actor::Base_s actor) {
					count_++;
					actor->serialize(*this, 0);
				}
				
				/** @brief Before saving.
				 * Implement the virtual savePre function.
				 * Record the position of the count data.
				 * Doing so enables @c this to load and save arrays whose length
				 * is unknown until all data is saved.
				 * This function is called by the initialization of an omessage object
				*/
				virtual void		pre() {
					// save the position of count
					pos_count_ = msg_->ss_.tellp();
					
					// allocate space for count
					msg->ar_ << count_;
				}
				/** @brief After saving.
				 * Implement the virtual savePost function. Overwrite the count data.
				*/
				virtual void		post() {
					auto pos = msg_->ss_.tellp();
					
					msg_->ss_.seekp(pos_count_);
					/** @todo determine if I count just say "ar << count" here */
					msg->ss_.write(count_, sizeof(count));
					
					msg_->ss_.seekp(pos);
				}
			};
			struct IUpdate: Update {
				/** @brief Load */
				Update&		operator>>(Neb::Scene::Base_s scene) {
					msg_->ar_ >> count_;
					
					Neb::Actor::Util::Address address;
					Neb::Actor::Base_s actor;
					for(int i = 0; i < count_; ++i) {
						msg_->ar_ >> address;
						
						actor = scene->getActor(address);
						assert(actor);
						
						msg_->ar_ >> *actor;
					}
					actor->serialize(*this, 0);
				}
				
			};
			
		}
	}
}

#endif



