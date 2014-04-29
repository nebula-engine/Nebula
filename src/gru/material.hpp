#ifndef __GLUTPP_MATERIAL_H__
#define __GLUTPP_MATERIAL_H__

#include <boost/serialization/nvp.hpp>

#include <gru/Color/Color.hpp>

namespace glutpp {
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

			gru::Color::color<float>	ambient_;
			gru::Color::color<float>	diffuse_;
			gru::Color::color<float>	specular_;
			gru::Color::color<float>	emission_;
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
