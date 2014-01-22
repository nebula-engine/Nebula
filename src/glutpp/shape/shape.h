#ifndef __GLUTPP_SHAPE_H__
#define __GLUTPP_SHAPE_H__

#include <map>


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gal/flag.h>

#include <math/vec4.h>
#include <math/vec3.h>
#include <math/vec2.h>
#include <math/transform.h>
#include <math/geo/polyhedron.h>

#include <glutpp/config.h>
#include <glutpp/glsl/program.h>
#include <glutpp/light/light.h>
#include <glutpp/shape/raw.h>
#include <glutpp/parent.h>
#include <glutpp/master.h>
#include <glutpp/material.h>
#include <glutpp/mesh.h>

namespace glutpp
{
	namespace shape
	{
		class buffer {
			public:
				GLuint		vbo_;
				GLuint		indices_;

				struct
				{
					std::shared_ptr<glutpp::texture>	image_;
				} texture_;
		};


		class shape: public glutpp::parent, public gal::flag<unsigned int>
		{
			public:
				typedef std::shared_ptr<glutpp::shape::buffer>		buffer_t;
				typedef std::map<glutpp::window::window*,buffer_t>	map_t;



				shape(glutpp::parent_s parent);
				~shape();
				unsigned int		f();
				void			f(unsigned int flag);
				math::mat44		get_pose();
				void			init(glutpp::shape::desc_s desc);
				void			release();
				void			cleanup();
				void			step(double time);
				void			notify_foundation_change_pose();
				void			load_lights(int& i, math::mat44 space);
				void			draw(
						glutpp::window::window_s window,
						math::mat44 space);

				void			model_load(math::mat44 space);
				void			init_buffer(
						glutpp::window::window_s window,
						std::shared_ptr<glutpp::glsl::program> p);

				void			draw_elements(glutpp::window::window_s window,
						math::mat44 space);
				void			i(int ni);
				int			i();

			private:
			public:

			public:
				// draw data

				int					i_;
				raw					raw_;


				gal::map<glutpp::light::light>		lights_;
				gal::map<glutpp::shape::shape>		shapes_;

				glutpp::material::material		material_front_;
				mesh					mesh_;

				map_t					context_;

				glutpp::program_name::e			program_;

				//glutpp::shape::parent_w		parent_;
		};
	}
}

#endif




