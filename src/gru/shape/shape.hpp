#ifndef __GLUTPP_SHAPE_H__
#define __GLUTPP_SHAPE_H__

#include <map>


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <galaxy/flag.hpp>

#include <math/vec4.hpp>
#include <math/vec3.hpp>
#include <math/vec2.hpp>
#include <math/transform.hpp>
#include <math/geo/polyhedron.hpp>

#include <gru/config.hpp>
#include <gru/glsl/program.hpp>
#include <gru/light/light.hpp>
#include <gru/shape/raw.hpp>
#include <gru/shape/parent.hpp>
#include <gru/master.hpp>
#include <gru/material.hpp>
#include <gru/mesh.hpp>

namespace glutpp {
	namespace shape {
		class buffer {
			public:
				GLuint		vbo_;
				GLuint		indices_;

				struct
				{
					std::shared_ptr<glutpp::texture>	image_;
				} texture_;
		};


		class shape:
			virtual public glutpp::shape::parent,
			public gal::flag<unsigned int>
		{
			public:
				typedef std::shared_ptr<glutpp::shape::buffer>		buffer_t;
				typedef std::map<glutpp::window::window*,buffer_t>	map_t;



				shape(glutpp::shape::parent_s parent);
				~shape();
				
				math::mat44<float>	getPose();
				math::mat44<float>	getPoseGlobal();
				
				glutpp::shape::parent_s	getParent();

				void		init(glutpp::shape::desc_s desc);
				void		release();
				void		cleanup();
				void		step(double time);
				void		notify_foundation_change_pose();
				void		load_lights(int& i, math::mat44<float> space);
				void		draw(glutpp::window::window_s, math::mat44<float> space);
	
				void		model_load(math::mat44<float> space);
				void		init_buffer(glutpp::window::window_s, std::shared_ptr<glutpp::glsl::program> p);

				void		draw_elements(glutpp::window::window_s, math::mat44<float> space);
				
				/** @name Index
				 * @{
				 */
				void		i(int ni);
				int		i();
				/** @} */
				/** @name Flag
				 * @{
				 */
				unsigned int	f();
				void		f(unsigned int flag);
				/** @} */
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

				glutpp::shape::parent_w			parent_;
		};
	}
}

#endif




