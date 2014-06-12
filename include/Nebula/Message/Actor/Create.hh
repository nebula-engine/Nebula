#ifndef __GLUTPP_NETWORK_ACTOR_CREATE_H__
#define __GLUTPP_NETWORK_ACTOR_CREATE_H__

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <Nebula/config.hh>
#include <Nebula/App/Base.hh>
#include <Nebula/Message/Actor/Event/Base.hh>
#include <Nebula/Actor/Base.hh>

namespace neb {
	namespace Message {
		namespace Actor {
			struct Create {
				public:
					void				load(neb::Actor::Base_s actor);

					template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
						ar & parent_i_;
						ar & i_;
						ar & wrapper_;
					}
				public:
					/** @brief parent index
					 *
					 * index of new object's parent
					 */
					gal::std::index_type				parent_i_;
					/** @brief index
					 *
					 * index of new object
					 */
					gal::std::index_type				i_;
					/** @brief Wrapper.
					 * wrapper to create the actor object
					 */
					gal::std::wrapper<neb::Actor::Base>		wrapper_;
			};
		}
	}
}





#endif


