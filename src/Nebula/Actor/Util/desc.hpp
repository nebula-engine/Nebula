#ifndef __NEBULA_ACTOR_DESC_H__
#define __NEBULA_ACTOR_DESC_H__


#include <boost/serialization/nvp.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/split_member.hpp>

#include <Nebula/master.hpp>
#include <Nebula/Actor/Util/Type.hpp>
#include <Nebula/Actor/Util/raw.hpp>
#include <Nebula/shape/desc.hpp>
#include <Nebula/Filter.hpp>
#include <Nebula/Typed.hpp>

namespace Neb {
	namespace Actor {
		class desc {
			public:
				friend class boost::serialization::access;
				desc();
				virtual ~desc() {}
				template<class Archive> void					serialize(Archive & ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("i",i_);
					ar & boost::serialization::make_nvp("raw",raw_wrapper_);
					ar & boost::serialization::make_nvp("actors",actors_);
					ar & boost::serialization::make_nvp("shapes",shapes_);
				}
				
				// make this an archive...
				desc&								operator<<(Neb::Actor::Base_w const & actor);
				void								load(Neb::Actor::Base_w const &);
				//void			add_shape(Neb::shape::desc);
				desc&								operator=(desc const &);

				boost::shared_ptr<Neb::Actor::raw>				getRaw();
			public:
				int							i_;
				Neb::WrapperTyped<Neb::Actor::raw>			raw_wrapper_;
				std::vector<Neb::Actor::desc_s>				actors_;
				std::vector<Neb::Shape::desc_s>				shapes_;


		};
	}
}

#endif








