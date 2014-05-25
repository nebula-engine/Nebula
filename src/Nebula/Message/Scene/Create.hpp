#ifndef __GLUTPP_NETWORK_MESSAGE_H__
#define __GLUTPP_NETWORK_MESSAGE_H__

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <Nebula/config.hh> // gru/config.hpp.in
//#include <Nebulahh>
#include <Nebula/Scene/Util/Address.hh>
//#include <Nebula/Actor/Util/Event.hh>
#include <Nebula/Actor/Base.hh>

namespace Neb {
	namespace Message {
		namespace Scene {
			struct Create {
				void load(Neb::Scene::Base_s scene);
				
				template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
					ar & i_;
					ar & scene_;
				}
				
				Neb::Util::index_type				i_;
				Neb::WrapperTyped<Neb::Scene::Base>		scene_;
			};
		}
	}
}

#endif



