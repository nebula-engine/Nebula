#ifndef __GLUTPP_SHAPE_H__
#define __GLUTPP_SHAPE_H__

#include <map>

#include <boost/weak_ptr.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#include <galaxy/flag.hpp>

/*
#include <math/vec4.hpp>
#include <math/vec3.hpp>
#include <math/vec2.hpp>
#include <math/transform.hpp>
#include <math/geo/polyhedron.hpp>
*/

#include <Nebula/Types.hpp>
#include <Nebula/shape/raw.hpp>
#include <Nebula/shape/parent.hpp>
#include <Nebula/master.hpp>

#include <Nebula/Graphics/glsl/program.hpp>
#include <Nebula/Graphics/Light/light.hpp>
#include <Nebula/Graphics/material.hpp>
#include <Nebula/Graphics/mesh.hpp>

namespace Neb {
	namespace Shape {
		class buffer {
			public:
				GLuint		vbo_;
				GLuint		indices_;

				struct
				{
					std::shared_ptr<Neb::texture>	image_;
				} texture_;
		};


		class shape: virtual public Neb::Shape::parent, public gal::flag {
			public:
				typedef std::shared_ptr<Neb::Shape::buffer>		buffer_t;
				typedef std::map<Neb::window::window*,buffer_t>	map_t;

				shape(Neb::Shape::parent_w parent);
				~shape();
				
				/** @name Accessors @{ */
				physx::PxTransform				getPose();
				physx::PxTransform				getPoseGlobal();
				Neb::Shape::parent_s				getParent();
				/** @} */

				void			init(Neb::Shape::desc_w desc);

				virtual void		createMesh() = 0;
				
				void			release();
				void			cleanup();
				void			step(double time);
				void			notify_foundation_change_pose();
				
				/** @name Rendering @{ */
				void			load_lights(int& i, physx::PxMat44 space);

				void			draw(Neb::window::window_s, physx::PxMat44 space);
	
				void			model_load(physx::PxMat44 space);
				void			init_buffer(Neb::window::window_s, std::shared_ptr<Neb::glsl::program> p);

				virtual void		draw_elements(Neb::window::window_s, physx::PxMat44 space);
				/** @} */
				/** @name Index
				 * @{
				 */
				void		i(int ni);
				int		i();
				/** @} */
				/** @name Flag
				 * @{
				 */
				//gal::flag::flag_type		f();
				//void				f(unsigned int flag);
				/** @} */
			protected:
				/** @brief Raw data. */
				Neb::Shape::Raw_s				raw_;
			public:
				// draw data

				/** @brief ID */
				int						i_;
				
				
				
				Neb::material::material				material_front_;
				mesh						mesh_;

				map_t						context_;

				Neb::program_name::e				program_;
				/** @brief Parent */
				Neb::Shape::parent_w				parent_;

				
				Neb::Map<Neb::Light::light>			lights_;
				

		};
		namespace Box {
			class Box: public Neb::Shape::shape {
				virtual void		createMesh();
			};
		}
		namespace Sphere {
			class Sphere: public Neb::Shape::shape {
				virtual void		createMesh();
			};
		}
		namespace Empty {
			class Empty: public Neb::Shape::shape {
				virtual void		createMesh();

				virtual void		draw_elements(Neb::window::window_s, physx::PxMat44 space) {}
			};
		}
	}
}

#endif




