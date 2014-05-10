#ifndef __GLUTPP_NETWORK_MESSAGE_H__
#define __GLUTPP_NETWORK_MESSAGE_H__

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <Nebula/config.hpp> // gru/config.hpp.in
#include <Nebula/master.hpp>
#include <Nebula/scene/desc.hpp>
#include <Nebula/actor/desc.hpp>
#include <Nebula/actor/addr.hpp>
#include <Nebula/actor/event.hpp>
#include <Nebula/actor/raw_factory.hpp>
#include <Nebula/actor/actor.hpp>

namespace Neb {
	namespace Message {
		namespace Scene {
			struct Create {
				void load(Neb::weak_ptr<glutpp::scene::scene> scene);
				
				template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
					ar & addr_;
					ar & desc_;
				}

				glutpp::scene::addr				addr_;
				Neb::WrapperTyped<Neb::Scene::scene>		desc_;
			};
		}
	}
}

#endif



