#ifndef __NEBULA_DESC_LIGHT_H__
#define __NEBULA_DESC_LIGHT_H__

#include <tinyxml2.h>

#include <math/raw/raw.h>
#include <math/vec3.h>
#include <math/vec4.h>
#include <math/color.h>

#include <gal/network/serial.h>

#include <glutpp/config.h>

namespace glutpp
{
	namespace light
	{

		class id: public gal::network::serial<id, gal::network::base>
		{
			public:
				void		load(glutpp::light::light_s);
				int i_;
		};

		class desc: public gal::network::serial_ext<id, raw>
		{
			public:
				//typedef glutpp::light::light<raw>	LIGHT;
				//typedef std::shared_ptr<LIGHT>		LIGHT_S;
				typedef std::shared_ptr<id>		ID_S;
				typedef std::shared_ptr<raw>		RAW_S;

				typedef gal::network::serial_ext<id, raw> SER;

				desc();
				void		load(glutpp::light::light_s);

				ID_S		get_id() { return std::get<0>(SER::tup_); }
				RAW_S		get_raw() { return std::get<1>(SER::tup_); }

		};
	}
}

#endif

