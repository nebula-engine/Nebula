#ifndef __GLUTPP_SCENE_RAW_H__
#define __GLUTPP_SCENE_RAW_H__

#include <gal/network/message.h>

#include <glutpp/actor/desc.h>

namespace glutpp
{
	namespace scene
	{
		struct raw: public gal::network::serial<raw>
		{
			public:
				raw();
				void			load(tinyxml2::XMLElement*);
				void			load(glutpp::scene::scene_s);

				unsigned int		flag_;
				math::vec3		gravity_;
		};
	}
}


#endif






