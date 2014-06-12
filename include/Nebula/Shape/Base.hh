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
#include <Nebula/Graphics/Light/Base.hh>
#include <Nebula/Graphics/Light/Util/Parent.hh>
#include <Nebula/Graphics/material.hh>
#include <Nebula/Graphics/mesh.hh>

namespace neb {
	namespace Shape {
		class buffer {
			public:
				GLuint		vbo_;
				GLuint		indices_;

				struct
				{
					sp::shared_ptr<neb::texture>	image_;
				} texture_;
		};

		class Base:
			virtual public neb::std::shared,
			public neb::Shape::Util::Parent,
			public neb::Light::Util::Parent
		{
			public:
				typedef ::std::map< neb::gfx::Context::Base*, sp::shared_ptr<buffer> >			map_t;

				Base();
				Base(sp::shared_ptr<neb::Shape::Util::Parent> parent);
				virtual ~Base();

				void			init();
				void			release();
				void			step(neb::core::TimeStep const & ts);

				/** @name Accessors @{ */
				mat4						getPose();
				mat4						getPoseGlobal();
				/** @} */


				virtual void					createMesh() = 0;


				/** @name Rendering @{ */
				void						load_lights(int& i, mat4 space);
				void						model_load(mat4 space);
				void						init_buffer(
						sp::shared_ptr<neb::gfx::Context::Base> context,
						sp::shared_ptr<neb::glsl::program> p);
				void						draw(
						sp::shared_ptr<neb::gfx::Context::Base>,
						mat4 space);
				virtual void					draw_elements(
						sp::shared_ptr<neb::gfx::Context::Base> context,
						mat4 space);
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
				sp::shared_ptr<neb::Shape::Util::Parent>		parent_;

			public:
				neb::Shape::Util::Flag		flag_;
				/** @brief Pose. */
				mat4				pose_;
				/** @brief Scale. */
				vec3				s_;
				/** @brief Name of image file */
				::std::string			image_;
				/** @brief Name of normal map file */
				::std::string			normal_;
				/** @brief Material. */
				neb::material::raw		material_;
			public:

				// draw data
				/** @brief ID */
				neb::material::material					material_front_;
				neb::gfx::mesh						mesh_;
				map_t							context_;
				neb::program_name::e					program_;
				/** @brief Parent */

		};
	}
}

#endif




