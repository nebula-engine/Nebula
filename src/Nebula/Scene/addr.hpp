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

#include <Nebula/config.hpp>
#include <Nebula/Scene/Types.hpp>

namespace Neb {
	namespace Scene {
		class Address {
			public:
				void						load(Neb::Scene::Base_w & scene);
				
				template<class Archive> void			serialize(Archive& ar, unsigned int const & version) {
					ar & vec_;
				}

				std::deque<int>					vec_;
		};
	}
}

#endif




