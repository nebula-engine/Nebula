#ifndef __GLUTPP_GFX_CORE_SHAPE_H__
#define __GLUTPP_GFX_CORE_SHAPE_H__

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gal/etc/timestep.hpp>

#include <neb/core/core/shape/base.hpp>
#include <neb/core/core/light/util/light_count.hpp>

#include <neb/gfx/core/light/util/parent.hpp>
#include <neb/gfx/texture.hpp>
#include <neb/gfx/material.hpp>
#include <neb/gfx/mesh/tri1.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/mesh/instanced.hpp>

#include <neb/phx/util/log.hpp>

namespace neb {
	namespace gfx {
		namespace context {
			class base;
		}

		namespace core { namespace shape {
			class base:
				virtual public neb::core::core::shape::base,
				virtual public neb::gfx::core::light::util::parent
			{
				public:
					
					base();
					virtual ~base();

					void			init(neb::core::core::shape::util::parent * const & p);
					void			release();
					void			step(gal::etc::timestep const & ts);
					virtual void		callbackPose(neb::core::pose const & pose_global);

					virtual weak_ptr<neb::core::core::light::base>		createLightPoint();
					virtual weak_ptr<neb::core::core::light::base>		createLightSpot(glm::vec3);
					virtual weak_ptr<neb::core::core::light::base>		createLightDirectional(glm::vec3);


					void							setPose(neb::core::pose const & pose);
					virtual void						createMesh();


					/** @name Rendering @{ */
					//void						load_lights(
					//		neb::core::core::light::util::count& light_count,
					//		neb::core::pose const & pose);
					void						model_load(
							neb::gfx::glsl::program::base const * const & p,
							neb::core::pose const & pose);
					
					void						init_buffer(
							neb::gfx::glsl::program::base const * const & p);

					virtual void					draw(
							neb::gfx::glsl::program::base const * const & p,
							neb::core::pose const & pose);
					virtual void					drawHF(
							neb::gfx::glsl::program::base const * const & p,
							neb::core::pose const & pose);
					
					virtual void					drawDebug(
							neb::gfx::glsl::program::base const * const & p,
							neb::core::pose const & pose);
					virtual void					draw_elements(
							neb::gfx::glsl::program::base const * const & p,
							neb::core::pose const & pose);
					/** @} */
				public:
					template<class Archive>	void	serialize(Archive & ar, unsigned int const & version) {
						LOG(lg, neb::phx::core::shape::sl, debug) << __PRETTY_FUNCTION__;
		
						ar & boost::serialization::make_nvp("flag",flag_);
						ar & boost::serialization::make_nvp("pose",pose_);
						ar & boost::serialization::make_nvp("scale",scale_);
						ar & boost::serialization::make_nvp("image",image_);
						ar & boost::serialization::make_nvp("normal",normal_);
						ar & boost::serialization::make_nvp("material",material_);
					}

				public:
					weak_ptr<neb::core::core::shape::util::parent>		parent_;

				public:
					/** @brief Material. */
					neb::material::raw					material_;
				public:

					// draw data
					/** @brief ID */
					std::shared_ptr<neb::gfx::mesh::tri1>			mesh_;
					//neb::program_name::e					program_;
					/** @brief Parent */
					
					std::shared_ptr<neb::gfx::mesh::instanced::slot_type>	mesh_slot_;
			};
		}}
	}
}


#endif





