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

namespace glutpp {
	namespace network {
		namespace actor {
			struct update {
				/** @brief Address and Data.
				 * @todo find a way to implement this using WrapperTyped or somehting like it
				 */
				struct addr_raw {
					/** @brief Load.
					 * Find the actor at the address and write directly into its Data object */
					template<class Archive> void	load(Archive & ar, unsigned int const & version) {
						ar & addr_;
						
						// find the actor
						auto actor = glutpp::master::Global()->getActor(addr_);
						if(!actor) throw 0; /** @todo handle this gracefully */
						
						ar & *(actor->raw_);
					}
					/** @brief Save.
					 * The pointer to the actor's Data object should already be set. */
					template<class Archive> void	save(Archive & ar, unsigned int const & version) const {
						ar & addr_;
						
						assert(raw_);
						
						ar & *raw_;
					}
					BOOST_SERIALIZATION_SPLIT_MEMBER();

					/** @brief Address. */
					glutpp::actor::addr			addr_;
					/** @brief Data pointer.
					 * could be replaced with Actor pointer with similar results */
					boost::shared_ptr<glutpp::actor::raw>	raw_;
				};
				
				//typedef vec_addr_raw::tuple tuple;
				
				void load(Neb::weak_ptr<glutpp::actor::actor> const & actor);
			
				template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
					ar & vector_;
				}	

				std::vector<boost::shared_ptr<glutpp::network::actor::update::addr_raw> >	vector_;
			};
		}
	}
}

#endif



