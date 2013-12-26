#ifndef __NEBULA_ACTOR_DESC_H__
#define __NEBULA_ACTOR_DESC_H__

#include <math/transform.h>
#include <math/raw/raw.h>

#include <glutpp/shape.h>

#include <neb/shape.h>

namespace neb
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
			CONTROLLER,
			LIGHT
		};
		struct filter_data
		{
			unsigned int word0;
			unsigned int word1;
			unsigned int word2;
			unsigned int word3;
		};
		struct desc
		{
			public:
				friend class neb::actor::Rigid_Actor;
			public:
				void			reset(){ num_shapes_ = 0; }

				int			load(tinyxml2::XMLElement*);
				int			add_shape(glutpp::shape_desc);

				neb::actor::type	type;

				math::raw::transform	pose;
				math::raw::vec3		velocity;
				float			density;

				struct
				{
					filter_data	simulation_;
					filter_data	scene_query_;
				} filter_data_;
			private:
				unsigned int		num_shapes_;
				glutpp::shape_desc	shapes_[10];
			public:
				int			parent;
				int			actors[20];
				int			actors_size;
				int			lights[20];
				int			lights_size;
		};
	}
}

#endif


