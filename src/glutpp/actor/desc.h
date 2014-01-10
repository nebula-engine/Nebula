#ifndef __NEBULA_ACTOR_DESC_H__
#define __NEBULA_ACTOR_DESC_H__

#include <math/transform.h>
#include <math/raw/raw.h>

#include <glutpp/shape/desc.h>


namespace glutpp
{
	namespace actor
	{
		enum type
		{
			NONE = 0,
			BASE,
			ACTOR,
			RIGID_ACTOR,
			RIGID_BODY,
			RIGID_DYNAMIC,
			RIGID_STATIC,
			PLANE,
			CONTROLLER,
			EMPTY
		};
		struct filter_data
		{
			unsigned int word0;
			unsigned int word1;
			unsigned int word2;
			unsigned int word3;
		};
		struct raw
		{
			public:
				void			load(tinyxml2::XMLElement*);
				void			plane(tinyxml2::XMLElement*);
				void			controller(tinyxml2::XMLElement*);


				void			write(gal::network::message_shared);
				void			read(gal::network::message_shared);
				size_t			size();




				glutpp::actor::type	type_;

				math::raw::transform	pose_;

				math::raw::vec3		n_;
				float			d_;

				math::raw::vec3		velocity_;
				float			density_;

				unsigned int		flag_;

				struct
				{
					filter_data	simulation_;
					filter_data	scene_query_;
				} filter_data_;
		};
		class desc
		{
			public:
				void			load(glutpp::actor::actor_shared);
				void			load(tinyxml2::XMLElement*);
				void			add_shape(glutpp::shape::desc);


				void			write(gal::network::message_shared);
				void			read(gal::network::message_shared);
				size_t			size();
			public:
				int			i_;

				glutpp::actor::raw	raw_;


				gal::network::vector_ext<glutpp::actor::desc>	actors_;
				gal::network::vector_ext<glutpp::shape::desc>	shapes_;

		};
	}
}

#endif








