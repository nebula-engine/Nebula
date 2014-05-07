#ifndef __NEBULA_PACKET_ACTOR_RELEASE_H__
#define __NEBULA_PACKET_ACTOR_RELEASE_H__

#include <vector>

#include <galaxy/network/message.hpp>

namespace neb {
	namespace packet {
		class actor_release {
			public:
				typedef std::shared_ptr<gal::network::message> msg_t;

				actor_release(int);				
				msg_t	serialize();
				void	write(char*&);
				void	read(char*&);
				size_t	size();
				
				
				int			scene_i_;
				int			actor_size_;
				std::vector<int>	actor_i_;
		};
	}
}

#endif
