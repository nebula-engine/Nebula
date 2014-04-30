#ifndef __GLUTPP_SCENE_ADDR_H__
#define __GLUTPP_SCENE_ADDR_H__

/*#include <galaxy/network/message.hpp>
#include <galaxy/network/serial.hpp>
#include <galaxy/network/vector.hpp>
*/

//#include <glutpp/actor/desc.h>
//#include <glutpp/actor/raw.h>
//#include <glutpp/scene/raw.h>

#include <gru/config.hpp>

namespace glutpp {
	namespace scene {
		//typedef gal::network::vector<int>	vec_int;
		//typedef std::shared_ptr<vec_int>	vec_int_s;


		class addr {
			public:
				void		load(boost::shared_ptr<glutpp::scene::scene> scene);
			
				template<class Archive> void	serialize(Archive& ar) {
					ar & vec_;
				}

				std::vector<int>	vec_;
		};
	}
}

#endif






