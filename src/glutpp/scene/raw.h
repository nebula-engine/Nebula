#ifndef __GLUTPP_SCENE_RAW_H__
#define __GLUTPP_SCENE_RAW_H__

#include <gal/network/message.h>

#include <glutpp/actor/desc.h>

namespace glutpp
{
	namespace scene
	{
		struct raw: public gal::network::serial<raw, gal::network::base>
		{
			public:
				raw();
				void			load(tinyxml2::XMLElement*);
				template<typename ACTOR> void load(std::shared_ptr<scene<ACTOR>> scene);

				unsigned int		flag_;
				math::vec3		gravity_;
		};
	}
}


#endif






