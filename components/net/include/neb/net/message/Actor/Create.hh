#ifndef __GLUTPP_NETWORK_ACTOR_CREATE_H__
#define __GLUTPP_NETWORK_ACTOR_CREATE_H__

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <neb/config.hh>
#include <neb/app/Base.hh>
#include <neb/message/Actor/Event/Base.hh>
#include <neb/core/actor/Base.hh>

namespace neb {
	namespace message {
		namespace actor {
			struct Create {
				public:
					void				load(std::shared_ptr<neb::core::actor::base> actor);

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
					gal::itf::index_type				parent_i_;
					/** @brief index
					 *
					 * index of new object
					 */
					gal::itf::index_type				i_;
					/** @brief Wrapper.
					 * wrapper to create the actor object
					 */
					gal::stl::wrapper<neb::core::actor::base>		wrapper_;
			};
		}
	}
}





#endif


