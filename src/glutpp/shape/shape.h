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
#include <glutpp/parent.h>
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
		class shape:
			public glutpp::parent,
			public gal::flag<unsigned int>
		{
			public:
				typedef std::shared_ptr<glutpp::shape::buffers>		buffer_t;
				typedef std::map<glutpp::window::window*,buffer_t>	map_t;



				shape(glutpp::parent_s);
				virtual ~shape();
				void				i(int);
				int				i();

				void				init(glutpp::shape::desc_s);
				void				release();
				void				cleanup();
				void				step(double);
				
				math::mat44			get_pose();


				void				notify_foundation_change_pose();

			private:
				void				init_buffer(
						glutpp::window::window_s,
						std::shared_ptr<glutpp::glsl::program>);
			public:

				virtual void			draw(
						glutpp::window::window_s,
						math::mat44);
				virtual void			draw_elements(
						glutpp::window::window_s,
						math::mat44);

				void				load_lights(int&, math::mat44);

				void				model_load(math::mat44);

				//glutpp::shape::desc_s	desc_generate();
			public:
				// draw data
				glutpp::material::material	material_front_;
				mesh				mesh_;
				map_t				context_;


				glutpp::light::light_m		lights_;
				glutpp::shape::shape_m		shapes_;


				//glutpp::shape::parent_w		parent_;

			public:
				int				i_;
				glutpp::shape::raw		raw_;

			private:
				unsigned int			f();
				void				f(unsigned int);
		};
	}
}

#endif




