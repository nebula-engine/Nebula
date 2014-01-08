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
			

				unsigned int		flag_;
				math::raw::vec3		gravity_;
				//size_t			actor_size_;
		};
		struct addr: public gal::network::serializeable
		{
			void	write(gal::network::message_shared);
			void	read(gal::network::message_shared);
			size_t	size();
			
			int	i_;
		};
		class desc: public id
		{
			public:
				desc();
				
				void		load(char const *);
				void		load(tinyxml2::XMLElement*);
				
				
				void		write(msg_t);
				void		read(msg_t);
				size_t		size();
				
				raw		raw_;
				
				gal::network::vector_ext<glutpp::actor::desc>	actors_;
		};
	}
}


#endif






