#ifndef __NEBULA_ACTIVE_TRANSFORMS_H__
#define __NEBULA_ACTIVE_TRANSFORMS_H__

#include <vector>

#include <gal/network/message.h>

#include <math/raw/raw.h>

#include <neb/config.h>

namespace neb
{
	namespace active_transform
	{
		struct node_raw
		{
			public:
				int			name_;
				math::raw::transform	pose_;
		};
		class node
		{
			public:

				size_t			size();
				void			write(char*&);
				void			read(char*&);



				node_raw		raw_;
		};
		struct set_raw
		{
			public:
				int			name_scene_;
				size_t			node_size_;
		};
		class set
		{
			public:
				typedef std::shared_ptr<gal::network::message> msg_t;

				set();
				void			push_back(neb::actor::Actor*);
				msg_t			serialize();
				size_t			size();
				void			write(char*&);
				void			read(char*&);

				set_raw			raw_;

				std::vector<node*>	nodes_;
		};
	}
}

#endif
