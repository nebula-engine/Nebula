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

		struct addr: gal::network::serial_ext<vec_int> {
			template<typename SCENE> void load(std::shared_ptr<SCENE> scene) {
				auto vec = std::get<0>(tup_);
				vec->vec_.clear();
				vec->vec_.push_back(scene->i());
			}

			vec_int_s	get_vec() { return std::get<0>(tup_); }
		};


		typedef gal::network::vector_ext<glutpp::actor::desc> vec_actor_desc;
		typedef std::shared_ptr<vec_actor_desc> vec_actor_desc_s;

		class desc: public gal::network::serial_ext<vec_actor_desc, raw, id>
		{
			public:
				desc();

				void			load(char const *);
				void			load(tinyxml2::XMLElement*);
				template<typename SCENE> void load(std::shared_ptr<SCENE> scene) {
					get_id()->load(scene);
					get_raw()->load(scene);

					// now
					for(auto it = scene->actors_.begin(); it != scene->actors_.end(); ++it)
					{
						auto actor = it->second;

						glutpp::actor::desc_s ad(new glutpp::actor::desc);

						ad->load(actor);

						ad->get_raw()->mode_create_ = glutpp::actor::mode_create::NOW;

						get_actors()->vec_.push_back(std::make_tuple(ad));
					}

					// deferred
					for(auto it = scene->actors_deferred_.begin(); it != scene->actors_deferred_.end(); ++it)
					{
						auto desc = it->second;

						glutpp::actor::desc_s ad(new glutpp::actor::desc);

						*ad = *desc;

						ad->get_raw()->mode_create_ = glutpp::actor::mode_create::DEFERRED;

						get_actors()->vec_.push_back(std::make_tuple(ad));
					}
				}		



				id_s			get_id();
				raw_s			get_raw();

				vec_actor_desc_s	get_actors();
		};
	}
}


#endif






