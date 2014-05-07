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





#include <Nebula/Math/Serialization.hpp>

#include <Nebula/config.hpp>
#include <Nebula/Graphics/material.hpp>
//#include <Nebula/shape/desc.hpp>
#include <Nebula/shape/raw.hpp>
#include <Nebula/Graphics/light/desc.hpp>

namespace Neb {
	namespace Shape {
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
				
				Neb::Shape::shape*		construct();
				
				template<class Archive> void	serialize(Archive& ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("i",i_);
					ar & boost::serialization::make_nvp("raw",raw_);
					ar & boost::serialization::make_nvp("shapes",shapes_);
					ar & boost::serialization::make_nvp("lights",lights_);
				}

				Neb::Shape::desc & 					operator<<(Neb::unique_ptr<Neb::Shape::shape> const &);
				//void			load(tinyxml2::XMLElement*);
				
				int							i_;
				Raw							raw_;
				std::vector<boost::shared_ptr<Neb::Shape::desc> >	shapes_;
				std::vector<boost::shared_ptr<Neb::light::desc> >	lights_;
		};
	}
}

#endif



