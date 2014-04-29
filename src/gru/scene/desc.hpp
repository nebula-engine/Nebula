#ifndef __GLUTPP_SCENE_DESC_H__
#define __GLUTPP_SCENE_DESC_H__

//#include <galaxy/network/message.hpp>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <gru/master.hpp>
#include <gru/actor/raw_factory.hpp>
#include <gru/Math/Serialization.hpp>

#include <gru/actor/desc.hpp>
#include <gru/actor/raw.hpp>
#include <gru/scene/raw.hpp>


namespace glutpp {
	namespace scene {
//		typedef gal::network::vector<int>	vec_int;
//		typedef std::shared_ptr<vec_int>	vec_int_s;
		
/*		struct id: public gal::network::serial<id, gal::network::base> {
			template<typename SCENE> void load(std::shared_ptr<SCENE> scene) {
				i_ = scene->i_;
			}
			int	i_;
		};
*/

//		typedef gal::network::vector_ext<glutpp::actor::desc>	vec_actor_desc;
//		typedef std::shared_ptr<vec_actor_desc>			vec_actor_desc_s;
		
		
		
		class desc {
			public:
				friend class boost::serialization::access;

				desc();

				template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("i",i_);
					ar & boost::serialization::make_nvp("type",type_);

					raw_.reset(new glutpp::scene::raw);

					ar & boost::serialization::make_nvp("raw",*raw_);
					ar & boost::serialization::make_nvp("actors",actors_);
				}

				void			load(char const *);
				//void			load(tinyxml2::XMLElement*);
				void			load(glutpp::scene::scene_s);
				
				
				int							i_;
				int							type_;
				boost::shared_ptr<glutpp::scene::raw>			raw_;
				
				std::vector<boost::shared_ptr<glutpp::actor::desc> >	actors_;
		};
	}
}


#endif






