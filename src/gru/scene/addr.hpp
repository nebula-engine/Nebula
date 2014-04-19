#ifndef __GLUTPP_SCENE_ADDR_H__
#define __GLUTPP_SCENE_ADDR_H__

#include <galaxy/network/message.hpp>
#include <galaxy/network/serial.hpp>

//#include <glutpp/actor/desc.h>
//#include <glutpp/actor/raw.h>
//#include <glutpp/scene/raw.h>


namespace glutpp
{
	namespace scene
	{
		typedef gal::network::vector<int>	vec_int;
		typedef std::shared_ptr<vec_int>	vec_int_s;


		class addr: public gal::network::serial_ext<vec_int> {
			public:
				void		load(glutpp::scene::scene_s scene);
				
				vec_int_s	get_vec() { return std::get<0>(tup_); }
		};
	}
}

#endif






