#ifndef __NEBULA_ACTOR_DESC_H__
#define __NEBULA_ACTOR_DESC_H__

#include <math/transform.h>
#include <math/raw/raw.h>

#include <glutpp/shape/desc.h>


namespace glutpp
{
	namespace actor
	{
		class Rigid_Actor;

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
			LIGHT,
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
				
				
				
				glutpp::actor::type	type_;

				math::raw::transform	pose_;
				
				math::raw::vec3		n_;
				float			d_;
				
				math::raw::vec3		velocity_;
				float			density_;

				struct
				{
					filter_data	simulation_;
					filter_data	scene_query_;
				} filter_data_;

		};
		class desc
		{
			public:
				void			load(tinyxml2::XMLElement*);
				void			add_shape(glutpp::shape::desc);



			public:
				glutpp::actor::raw	raw_;
				
				
				std::vector<glutpp::actor::desc*>	actors_;
				std::vector<glutpp::shape::desc*>	shapes_;

		};
	}
}

#endif








