#ifndef __NEBULA_ACTOR_DESC_H__
#define __NEBULA_ACTOR_DESC_H__


#include <boost/serialization/nvp.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/split_member.hpp>

#include <Nebula/master.hpp>
#include <Nebula/Actor/Util/Type.hpp>
//#include <Nebula/Actor/Util/id.hpp>
#include <Nebula/Actor/Util/raw.hpp>
//#include <Nebula/Actor/raw_factory.hpp>
#include <Nebula/shape/desc.hpp>
#include <Nebula/Filter.hpp>
#include <Nebula/Typed.hpp>

namespace glutpp {
	namespace actor {
		class desc {
			public:
				friend class boost::serialization::access;
				desc();
				virtual ~desc() {}
				template<class Archive> void					serialize(Archive & ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("i",i_);
					ar & boost::serialization::make_nvp("type",type_);
					ar & boost::serialization::make_nvp("raw",raw_wrapper_);
					ar & boost::serialization::make_nvp("actors",actors_);
					ar & boost::serialization::make_nvp("shapes",shapes_);
				}
				
				// make this an archive...
				desc&								operator<<(boost::shared_ptr<Neb::Actor::Base> const & actor);
				void								load(Neb::unique_ptr<Neb::Actor::Base> const &);
				//void			add_shape(Neb::shape::desc);
				desc&								operator=(desc const &);

				boost::shared_ptr<Neb::Actor::raw>				getRaw();
			public:
				int								i_;
				Neb::Actor::Type						type_;
				//boost::shared_ptr<Nebula::Actor::raw>				raw_;
				Neb::WrapperTyped<Neb::Actor::raw>				raw_wrapper_;
				std::vector<boost::shared_ptr<Neb::Actor::desc> >		actors_;
				std::vector<boost::shared_ptr<Neb::Shape::desc> >		shapes_;


		};
	}
}

#endif








