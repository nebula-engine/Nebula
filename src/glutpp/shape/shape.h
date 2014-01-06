#ifndef __GLUTPP_SHAPE_H__
#define __GLUTPP_SHAPE_H__

#include <map>

#include <GLFW/glfw3.h>

#include <gal/flag.h>

#include <math/vec4.h>
#include <math/vec3.h>
#include <math/vec2.h>
#include <math/transform.h>
#include <math/geo/polyhedron.h>

#include <glutpp/config.h>
#include <glutpp/shape/desc.h>
#include <glutpp/material.h>
#include <glutpp/mesh.h>

namespace glutpp
{
	namespace shape
	{
		struct buffers
		{
			GLuint		vbo_;
			GLuint		indices_;
			
			struct
			{
				std::shared_ptr<glutpp::texture>	image_;
			} texture_;
		};
		class shape: public std::enable_shared_from_this<shape>, public gal::flag
		{
			public:
				enum flag
				{
					SHOULD_DELETE = 1 << 0,
					IMAGE = 1 << 1
				};

				typedef std::shared_ptr<glutpp::shape::buffers>		buffer_t;
				typedef std::map<glutpp::window::window*,buffer_t>	map_t;



				shape(glutpp::actor::actor_shared, glutpp::shape::desc_shared);
				virtual ~shape();
				void			i(int);

				void			init();
				void			release();
				void			cleanup();
				
				math::mat44		get_pose();
				
						private:
				void			init_buffer(
						glutpp::window::window_shared,
						std::shared_ptr<glutpp::glsl::program>);
			public:

				virtual void			draw(
						glutpp::window::window_shared,
						math::mat44);
				virtual void			draw_elements(
						glutpp::window::window_shared,
						math::mat44);

				void				load_lights(int&);

				void				model_load(math::mat44);

				glutpp::shape::desc_shared	desc_generate();
			public:
				// draw data
				material			material_front_;
				mesh				mesh_;
				map_t				context_;

				glutpp::shape::desc_shared	desc_;
				
				glutpp::light::light_map	lights_;
				glutpp::shape::shape_map	shapes_;
				
				
				glutpp::actor::actor_weak	actor_;
		};
	}
}

#endif




