#ifndef __GLUTPP_SCENE_RAW_H__
#define __GLUTPP_SCENE_RAW_H__

#include <tinyxml2.h>

//#include <galaxy/network/message.hpp>
//#include <galaxy/network/serial.hpp>

#include <boost/serialization/nvp.hpp>

#include <PxPhysicsAPI.h>

//#include <math/vec3.hpp>

#include <gru/config.hpp>
//#include <gru/actor/desc.hpp>

namespace glutpp {
	namespace scene {
		class raw {
			public:
				raw();
				//void					load(tinyxml2::XMLElement*);
				void					load(glutpp::scene::scene_s scene);

				template <class Archive> void		serialize(Archive & ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("flag",flag_);
					ar & boost::serialization::make_nvp("gravity",gravity_);
				}
				
				unsigned int		flag_;
				physx::PxVec3		gravity_;
		};
	}
}


#endif






