#ifndef __GLUTPP_MATERIAL_H__
#define __GLUTPP_MATERIAL_H__

#include <boost/serialization/nvp.hpp>

#include <gal/std/timestep.hpp>
#include <Nebula/gfx/Color/Color.hh>

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

			neb::Color::color<float>	ambient_;
			neb::Color::color<float>	diffuse_;
			neb::Color::color<float>	specular_;
			neb::Color::color<float>	emission_;
			float				shininess_;
		};

		class material
		{
			public:
				material();
				void		init();
				void		release();
				void		step(gal::std::timestep const & ts);
				/** @brief load
				 *
				 * load into OpenGL
				 */
				void		load();
				raw		raw_;
		};
	}
}

#endif
