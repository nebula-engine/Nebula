#ifndef __GLUTPP_SCENE_RAW_H__
#define __GLUTPP_SCENE_RAW_H__

#include <tinyxml2.h>

#include <galaxy/network/message.hpp>
#include <galaxy/network/serial.hpp>

#include <math/vec3.hpp>

#include <gru/config.hpp>
//#include <gru/actor/desc.hpp>

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
				math::vec3<double>	gravity_;
		};
	}
}


#endif






