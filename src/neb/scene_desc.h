#ifndef __NEBULA_SCENE_DESC_H__
#define __NEBULA_SCENE_DESC_H__

#include <neb/actor/desc.h>

namespace neb
{
	struct scene_desc;
	
	class scene_desc_inter
	{
		public:
			scene_desc_inter();
			void		load(tinyxml2::XMLElement*);
			scene_desc*	generate();
	};

	struct scene_desc
	{
		
		
		
		
		int			name_;
		
		math::raw::vec3		gravity_;
		
		neb::actor::desc*	actor_;
	};
}

#endif
