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

		typedef std::shared_ptr<Neb::Shape::buffer>			buffer_s;

		class Base:
			virtual public Neb::Shape::Util::Parent,
			virtual public Neb::Light::Util::Parent
		{
			public:
				typedef std::map<Neb::Graphics::Window::Base*,buffer_s>			map_t;

				Base();
				Base(Neb::Shape::Util::Parent_s parent);
				~Base();

				/** @name Accessors @{ */
				mat4						getPose();
				mat4						getPoseGlobal();
				Neb::Shape::Util::Parent_s			getParent();
				/** @} */

				void			init();
				void			release();
				void			step(Neb::Core::TimeStep const & ts);

				virtual void		createMesh() = 0;

				void			notify_foundation_change_pose();

				/** @name Rendering @{ */
				void			load_lights(int& i, mat4 space);

				void			draw(Neb::Graphics::Window::Base_s, mat4 space);

				void			model_load(mat4 space);
				void			init_buffer(Neb::Graphics::Window::Base_s, std::shared_ptr<Neb::glsl::program> p);

				virtual void		draw_elements(Neb::Graphics::Window::Base_s, mat4 space);
				/** @} */
				/** @name Index
				 * @{
				 */
				void		i(int ni);
				int		i();
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
				Neb::Shape::Util::Flag		flag_;
				/** @brief Pose. */
				mat4				pose_;
				/** @brief Scale. */
				vec3				s_;
				/** @brief Name of image file */
				std::string			image_;
				/** @brief Name of normal map file */
				std::string			normal_;
				/** @brief Material. */
				Neb::material::raw		material_;
			public:
				// draw data
				/** @brief ID */
				int						i_;
				Neb::material::material				material_front_;
				mesh						mesh_;
				map_t						context_;
				Neb::program_name::e				program_;
				/** @brief Parent */
				Neb::Shape::Util::Parent_w			parent_;
		};

		class Empty: public Neb::Shape::Base {
			virtual void		createMesh();

			virtual void		draw_elements(Neb::Graphics::Window::Base_s, mat4 space) {}
		};
	}
}

#endif




