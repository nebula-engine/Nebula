#ifndef __GLUTPP_SCENE_DESC_H__
#define __GLUTPP_SCENE_DESC_H__

//#include <galaxy/network/message.hpp>
/*
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/nvp.hpp>


#include <Nebula/master.hpp>
//#include <Nebula/actor/raw_factory.hpp>
#include <Nebula/Math/Serialization.hpp>

#include <Nebula/Actor/Util/desc.hpp>
#include <Nebula/Actor/Util/raw.hpp>
#include <Nebula/Scene/raw.hpp>
#include <Nebula/Util/Typed.hpp>

namespace Neb {
	namespace Scene {
		class desc {
			public:
				friend class boost::serialization::access;
				
				desc();
				virtual ~desc() {}

				template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("i",i_);
					ar & boost::serialization::make_nvp("type",type_);
					ar & boost::serialization::make_nvp("raw",raw_wrapper_);
					/ ** @todo no idea why this fails * /
					//ar & boost::serialization::make_nvp("actors",actors_);
				}

				void			load(char const *);
				//void			load(tinyxml2::XMLElement*);
				void			load(Neb::Scene::scene_w);
				
				
				int							i_;
				int							type_;
				Neb::WrapperTyped<Neb::Scene::raw>			raw_wrapper_;
				std::vector<Neb::Actor::desc_w>				actors_;
		};
	}
}

*/
#endif






