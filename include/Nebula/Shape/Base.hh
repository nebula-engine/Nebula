#ifndef __GLUTPP_SHAPE_H__
#define __GLUTPP_SHAPE_H__

#include <map>

#include <boost/weak_ptr.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Nebula/Types.hh>
#include <Nebula/Core/TimeStep.hpp>
#include <Nebula/Util/typedef.hpp>
#include <Nebula/Graphics/Types.hh>

#include <Nebula/Shape/Util/Parent.hh>
#include <Nebula/Shape/Util/Flag.hh>

#include <Nebula/Graphics/glsl/program.hh>
//#include <Nebula/Graphics/Light/Base.hh>
#include <Nebula/Graphics/Light/Util/Parent.hh>
#include <Nebula/Graphics/Light/Util/light_count.hpp>
#include <Nebula/Graphics/material.hh>
#include <Nebula/Graphics/mesh.hh>

namespace neb { namespace core { namespace shape {


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
			virtual public neb::std::shared,
			virtual public neb::core::shape::util::parent,
			virtual public neb::Light::util::parent
		{
			public:
				typedef ::std::map< neb::gfx::context::base*, sp::shared_ptr<buffer> >			map_t;

				base(sp::shared_ptr<neb::core::shape::util::parent> parent);
				virtual ~base();

				void			init();
				void			release();
				void			step(neb::core::TimeStep const & ts);

				/** @name Accessors @{ */
				neb::core::pose						getPose();
				neb::core::pose						getPoseGlobal();
				/** @} */


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
				sp::shared_ptr<neb::core::shape::util::parent>		parent_;

			public:
				neb::core::shape::util::Flag		flag_;
				/** @brief pose */
				neb::core::pose				pose_;
				/** @brief scale */
				vec3					s_;
				/** @brief Name of image file */
				::std::string				image_;
				/** @brief Name of normal map file */
				::std::string				normal_;
				/** @brief Material. */
				neb::material::raw			material_;
			public:

				// draw data
				/** @brief ID */
				neb::material::material					material_front_;
				neb::gfx::mesh						mesh_;
				map_t							context_;
				neb::program_name::e					program_;
				/** @brief Parent */

		};

}}}


#endif





