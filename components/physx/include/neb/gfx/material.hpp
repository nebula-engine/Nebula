#ifndef __GLUTPP_MATERIAL_H__
#define __GLUTPP_MATERIAL_H__

#include <memory>

#include <boost/serialization/nvp.hpp>

#include <gal/etc/timestep.hpp>

#include <neb/core/color/Color.hh>

#include <neb/gfx/glsl/util/decl.hpp>

namespace neb {
	namespace material {

		struct raw {
			raw();
			
			template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
				ar & boost::serialization::make_nvp("ambient",ambient_);
				ar & boost::serialization::make_nvp("diffuse",diffuse_);
				ar & boost::serialization::make_nvp("specular",specular_);
				ar & boost::serialization::make_nvp("emission",emission_);
				ar & boost::serialization::make_nvp("shininess",shininess_);
			}

			neb::core::color::color	ambient_;
			neb::core::color::color	diffuse_;
			neb::core::color::color	specular_;
			neb::core::color::color	emission_;
			float				shininess_;
		};

		class material
		{
			public:
				material();
				void		init();
				void		release();
				void		step(gal::etc::timestep const & ts);
				/** @brief load
				 *
				 * load into OpenGL
				 */
				void		load(std::shared_ptr<neb::gfx::glsl::program::base> p);
				raw		raw_;
		};
	}
}

#endif
