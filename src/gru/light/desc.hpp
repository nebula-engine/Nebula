#ifndef __NEBULA_DESC_LIGHT_H__
#define __NEBULA_DESC_LIGHT_H__

#include <tinyxml2.h>

/*
//#include <math/raw/raw.h>
#include <math/vec3.hpp>
#include <math/vec4.hpp>
#include <math/color.hpp>
*/
//#include <galaxy/network/serial.hpp>

#include <gru/config.hpp>
#include <gru/light/raw.hpp>

namespace glutpp {
	namespace light {

		class id {
			public:
				void		load(glutpp::light::light_s);
				
				template<class Archive> void	serialize(Archive& ar) {

				}
				
				int i_;
		};

		class desc {
			public:
				desc();
				void		load(glutpp::light::light_s);

				//ID_S		get_id() { return std::get<0>(SER::tup_); }
				//RAW_S		get_raw() { return std::get<1>(SER::tup_); }
				
				id		id_;
				raw		raw_;
				
		};
	}
}

#endif

