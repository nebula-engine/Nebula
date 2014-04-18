#ifndef __GLUTPP_SCENE_RAW_H__
#define __GLUTPP_SCENE_RAW_H__

#include <tinyxml2.h>

#include <gal/network/message.h>
#include <gal/network/serial.h>

#include <math/vec3.h>

#include <glutpp/config.h>
//#include <glutpp/actor/desc.h>

namespace glutpp
{
	namespace scene
	{
		class raw: public gal::network::serial<raw, gal::network::base>
		{
			public:
				raw();
				void			load(tinyxml2::XMLElement*);
				void			load(glutpp::scene::scene_s scene);

				unsigned int		flag_;
				math::vec3		gravity_;
		};
	}
}


#endif






