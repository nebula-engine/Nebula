#ifndef __NEBULA_ACTOR_ADDR_H__
#define __NEBULA_ACTOR_ADDR_H__

#include <math/transform.h>
#include <math/raw/raw.h>

#include <glutpp/scene/desc.h>
#include <glutpp/actor/actor.h>

namespace glutpp
{
	namespace actor
	{
		typedef gal::network::vector<int> vec_int;
		typedef std::shared_ptr<vec_int> vec_int_s;



		class addr: public gal::network::serial_ext<vec_int, glutpp::scene::addr> {
			public:
				template<typename ACTOR> void load_this(std::shared_ptr<ACTOR> actor) {
					assert(actor);

					load_parent(actor);

					int i = actor->i();
					get_vec()->vec_.push_back(i);
				}
				template<typename ACTOR> void load_parent(std::shared_ptr<ACTOR> actor0) {
					assert(actor0);

					auto parent = actor0->get_parent();

					auto scene = std::dynamic_pointer_cast<glutpp::scene::scene>(parent);
					auto actor1 = std::dynamic_pointer_cast<ACTOR>(parent);

					if(actor1)
					{
						load_this(actor1);
					}
					else
					{
						assert(scene);
						get_scene_addr()->load(scene);
					}
				}
				//glutpp::actor::actor_shared	actor_;

				glutpp::scene::addr_s	get_scene_addr();
				vec_int_s		get_vec();
		};
	}
}

#endif








