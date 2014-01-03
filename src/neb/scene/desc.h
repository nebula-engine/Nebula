#ifndef __NEBULA_SCENE_DESC_H__
#define __NEBULA_SCENE_DESC_H__

#include <glutpp/actor/desc.h>

namespace neb
{
	namespace scene
	{
		struct raw
		{
			public:
				void			load(tinyxml2::XMLElement*);
			

				int			name_;
				math::raw::vec3		gravity_;
		};

		class desc
		{
			public:
				void				load(char const *);
				void				load(tinyxml2::XMLElement*);
				


				raw				raw_;

				std::vector<glutpp::actor::desc*>	actors_;
		};
	}
}


#endif
