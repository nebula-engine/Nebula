#ifndef __GLUTPP_SHAPE_H__
#define __GLUTPP_SHAPE_H__

#include <map>

#include <boost/weak_ptr.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gal/std/timestep.hpp>

//#include <neb/util/decl.hpp>
#include <neb/typedef.hpp>
//#include <neb/gfx/util/decl.hpp>

#include <neb/core/shape/util/Parent.hh>
#include <neb/core/shape/util/Flag.hh>

//#include <neb/gfx/glsl/program.hh>
//#include <neb/core/light/base.hpp>
#include <neb/core/light/util/parent.hpp>
#include <neb/core/light/util/light_count.hpp>
//#include <neb/gfx/material.hpp>
//#include <neb/gfx/mesh.hh>

namespace neb { 

	namespace gfx { namespace core { namespace shape {
		class base;
	}}}

	namespace core {
		namespace light {
			class base;
		}


		namespace shape {



			class base:
				virtual public neb::std::shared,
				virtual public neb::core::shape::util::parent,
				virtual public neb::core::light::util::parent
			{
				public:

					base(sp::shared_ptr<neb::core::shape::util::parent> parent);
					virtual ~base();

					void			init();
					void			release();
					void			step(gal::std::timestep const & ts);

					/** @name Accessors @{ */
					neb::core::pose						getPose();
					neb::core::pose						getPoseGlobal();
					/** @} */


					sp::weak_ptr<neb::core::light::base>			createLightPoint();



				public:
					template<class Archive>	void	serialize(Archive & ar, unsigned int const & version) {
						ar & boost::serialization::make_nvp("flag",flag_);
						ar & boost::serialization::make_nvp("pose",pose_);
						ar & boost::serialization::make_nvp("s",s_);
						ar & boost::serialization::make_nvp("image",image_);
						ar & boost::serialization::make_nvp("normal",normal_);
					}

				public:
					sp::weak_ptr<neb::core::shape::util::parent>		parent_;

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
				public:


			};

		}
	}
}


#endif





