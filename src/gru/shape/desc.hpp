#ifndef __GLUTPP_SHAPE_DESC_H__
#define __GLUTPP_SHAPE_DESC_H__

#include <vector>

#include <tinyxml2.h>

//#include <math/vec3.hpp>
//#include <math/raw/raw.hpp>

//#include <galaxy/network/serial.hpp>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>





#include <gru/Math/Serialization.hpp>

#include <gru/config.hpp>
#include <gru/Graphics/material.hpp>
//#include <gru/shape/desc.hpp>
#include <gru/shape/raw.hpp>
#include <gru/Graphics/light/desc.hpp>

namespace glutpp {
	namespace shape {
		class id {
			public:
				template<class Archive> void	serialize(Archive& ar) {
					ar & i_;
				}

				int i_;
		};

		class desc {
			public:
				desc();
				
				glutpp::shape::shape*		construct();
				
				template<class Archive> void	serialize(Archive& ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("i",i_);
					ar & boost::serialization::make_nvp("raw",raw_);
					ar & boost::serialization::make_nvp("shapes",shapes_);
					ar & boost::serialization::make_nvp("lights",lights_);
				}

				glutpp::shape::desc & 		operator<<(Neb::unique_ptr<glutpp::shape::shape> const &);
				//void			load(tinyxml2::XMLElement*);
				
				int							i_;
				Raw							raw_;
				std::vector<boost::shared_ptr<glutpp::shape::desc> >	shapes_;
				std::vector<boost::shared_ptr<glutpp::light::desc> >	lights_;
		};
	}
}

#endif



