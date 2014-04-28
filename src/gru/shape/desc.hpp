#ifndef __GLUTPP_SHAPE_DESC_H__
#define __GLUTPP_SHAPE_DESC_H__

#include <vector>

#include <tinyxml2.h>

//#include <math/vec3.hpp>
//#include <math/raw/raw.hpp>

//#include <galaxy/network/serial.hpp>

#include <gru/config.hpp>
#include <gru/material.hpp>
//#include <gru/shape/desc.hpp>
#include <gru/shape/raw.hpp>
#include <gru/light/desc.hpp>

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
				
				template<class Archive> void	serialize(Archive& ar) {
					ar & i_;
					ar & raw_;
					ar & shapes_;
					ar & lights_;
				}

				void			load(glutpp::shape::shape_s);
				//void			load(tinyxml2::XMLElement*);
				
				int					i_;
				Raw					raw_;
				std::vector<glutpp::shape::desc_s>	shapes_;
				std::vector<glutpp::light::desc_s>	lights_;
		};
	}
}

#endif



