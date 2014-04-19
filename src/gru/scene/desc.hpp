#ifndef __GLUTPP_SCENE_DESC_H__
#define __GLUTPP_SCENE_DESC_H__

#include <gal/network/message.h>

#include <glutpp/actor/desc.h>
#include <glutpp/actor/raw.h>
#include <glutpp/scene/raw.h>

namespace glutpp
{
	namespace scene
	{
		typedef gal::network::vector<int>	vec_int;
		typedef std::shared_ptr<vec_int>	vec_int_s;
		
		struct id: public gal::network::serial<id, gal::network::base> {
			template<typename SCENE> void load(std::shared_ptr<SCENE> scene) {
				i_ = scene->i_;
			}
			int	i_;
		};


		typedef gal::network::vector_ext<glutpp::actor::desc>	vec_actor_desc;
		typedef std::shared_ptr<vec_actor_desc>			vec_actor_desc_s;
		
		
		
		class desc: public gal::network::serial_ext<
			    id,
			    raw,
			    vec_actor_desc>
		{
			public:
				typedef gal::network::serial_ext<id,raw,vec_actor_desc> SER;
				

				desc();

				void			load(char const *);
				void			load(tinyxml2::XMLElement*);
				void			load(glutpp::scene::scene_s);


				id_s			get_id();
				raw_s			get_raw();

				vec_actor_desc_s	get_actors();
		};
	}
}


#endif






