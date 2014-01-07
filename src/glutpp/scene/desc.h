#ifndef __GLUTPP_SCENE_DESC_H__
#define __GLUTPP_SCENE_DESC_H__

#include <gal/network/message.h>

#include <glutpp/actor/desc.h>

namespace glutpp
{
	namespace scene
	{
		struct raw
		{
			public:
				void			reset();
				void			load(tinyxml2::XMLElement*);
			

				int			i_;
				unsigned int		flag_;
				math::raw::vec3		gravity_;
				size_t			actor_size_;
		};

		class desc
		{
			public:
				typedef gal::network::message::shared_t msg_t;
				
				desc();
				void		load(char const *);
				void		load(tinyxml2::XMLElement*);
				
				msg_t		serialize();
				size_t		size();
				void		read(char*&);
		
				raw		raw_;
				
				std::vector<glutpp::actor::desc_shared>		actors_;
		};
	}
}


#endif






