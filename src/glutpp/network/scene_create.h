#ifndef __NEBULA_NETWORK_SCENE_CREATE_H__
#define __NEBULA_NETWORK_SCENE_CREATE_H__

#include <gal/network/message_ext.h>

namespace glutpp
{
	namespace network
	{
		class scene_create:
			public gal::network::message_ext<
			gal::network::vector<glutpp::actor::desc>,
			glutpp::scene::desc>
		{
			public:
				scene_create(int);
		};
	}
}

#endif



