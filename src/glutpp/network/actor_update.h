#ifndef __NEBULA_NETWORK_ACTOR_UPDATE_H__
#define __NEBULA_NETWORK_ACTOR_UPDATE_H__

#include <gal/network/vector.h>
#include <gal/network/serializeable.h>

#include <glutpp/config.h>
#include <glutpp/scene/desc.h>

namespace glutpp
{
	namespace network
	{
		class actor_update: public gal::network::serializeable
		{
			public:
				
				virtual void    write(gal::network::message_shared);
                                virtual void    read(gal::network::message_shared);
                                virtual size_t  size();
				
				
				int						scene_i_;
				gal::network::vector<glutpp::actor::raw>	actors_;
		};
	}
}

#endif

