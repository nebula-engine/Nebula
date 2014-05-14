#ifndef __GLUTPP_SCENE_ADDR_H__
#define __GLUTPP_SCENE_ADDR_H__

/*#include <galaxy/network/message.hpp>
#include <galaxy/network/serial.hpp>
#include <galaxy/network/vector.hpp>
*/

//#include <glutpp/actor/desc.h>
//#include <glutpp/actor/raw.h>
//#include <glutpp/scene/raw.h>

#include <deque>

#include <Nebula/config.hh>
#include <Nebula/Scene/Util/Types.hh>

namespace Neb {
	namespace Scene {
		class Address {
			public:
				void						load(Neb::Scene::Base_s & scene);
				
				template<class Archive> void			serialize(Archive& ar, unsigned int const & version) {
					ar & vec_;
				}

				std::deque<int>					vec_;
		};
	}
}

#endif




