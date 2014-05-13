#ifndef __GLUTPP_MATERIAL_H__
#define __GLUTPP_MATERIAL_H__

#include <boost/serialization/nvp.hpp>

#include <Nebula/Graphics/Color/Color.hh>

namespace Neb {
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

			Neb::Color::color<float>	ambient_;
			Neb::Color::color<float>	diffuse_;
			Neb::Color::color<float>	specular_;
			Neb::Color::color<float>	emission_;
			float				shininess_;
		};

		class material
		{
			public:
				material();
				void		init();
				void		load();
				void		step(double);

				raw		raw_;
		};
	}
}

#endif
