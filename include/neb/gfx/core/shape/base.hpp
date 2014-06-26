#ifndef __GLUTPP_GFX_CORE_SHAPE_H__
#define __GLUTPP_GFX_CORE_SHAPE_H__

#include <map>

#include <boost/weak_ptr.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gal/std/timestep.hpp>

//#include <neb/util/decl.hpp>
#include <neb/typedef.hpp>
//#include <neb/gfx/util/decl.hpp>

#include <neb/core/shape/base.hpp>

//#include <neb/gfx/glsl/program.hh>
//#include <neb/core/light/base.hpp>
#include <neb/gfx/core/light/util/parent.hpp>

#include <neb/core/light/util/light_count.hpp>

#include <neb/gfx/texture.hh>
#include <neb/gfx/material.hpp>
#include <neb/gfx/mesh.hh>

namespace neb {
	namespace glsl {
		class program;
	}

	namespace gfx {


		namespace context {
			class base;
		}

		namespace core { namespace shape {


			class buffer {
				public:
					GLuint		vbo_;
					GLuint		indices_;

					struct
					{
						sp::shared_ptr<neb::texture>	image_;
					} texture_;
			};

			class base:
				virtual public neb::core::shape::base,
				virtual public neb::gfx::core::light::util::parent
			{
				public:
					typedef ::std::map< neb::gfx::context::base*, sp::shared_ptr<buffer> >			map_t;

					base(sp::shared_ptr<neb::core::shape::util::parent> parent);
					virtual ~base();

					void			init();
					void			release();
					void			step(gal::std::timestep const & ts);

					/** @name Accessors @{ */
					neb::core::pose						getPose();
					neb::core::pose						getPoseGlobal();
					/** @} */

					virtual sp::weak_ptr<neb::core::light::base>		createLightPoint();


					virtual void					createMesh() = 0;


					/** @name Rendering @{ */
					void						load_lights(neb::core::light::util::count& light_count, neb::core::pose const & pose);
					void						model_load(neb::core::pose const & pose);
					void						init_buffer(
							sp::shared_ptr<neb::gfx::context::base> context,
							sp::shared_ptr<neb::glsl::program> p);
					void						draw(
							sp::shared_ptr<neb::gfx::context::base>,
							sp::shared_ptr<neb::glsl::program> p,
							neb::core::pose const & pose);
					virtual void					draw_elements(
							sp::shared_ptr<neb::gfx::context::base> context,
							sp::shared_ptr<neb::glsl::program> p,
							neb::core::pose const & pose);
					/** @} */
				public:
					template<class Archive>	void	serialize(Archive & ar, unsigned int const & version) {
						ar & boost::serialization::make_nvp("flag",flag_);
						ar & boost::serialization::make_nvp("pose",pose_);
						ar & boost::serialization::make_nvp("s",s_);
						ar & boost::serialization::make_nvp("image",image_);
						ar & boost::serialization::make_nvp("normal",normal_);
						ar & boost::serialization::make_nvp("material",material_);
					}

				public:
					sp::weak_ptr<neb::core::shape::util::parent>		parent_;

				public:
					/** @brief Material. */
					neb::material::raw			material_;
				public:

					// draw data
					/** @brief ID */
					neb::material::material					material_front_;
					neb::gfx::mesh						mesh_;
					map_t							context_;
					//neb::program_name::e					program_;
					/** @brief Parent */

			};

		}}
	}
}


#endif





