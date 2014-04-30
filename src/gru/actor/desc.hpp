#ifndef __NEBULA_ACTOR_DESC_H__
#define __NEBULA_ACTOR_DESC_H__

//#include <math/transform.hpp>

//#include <galaxy/network/serial.hpp>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/split_member.hpp>

#include <gru/master.hpp>
#include <gru/actor/Type.hpp>
#include <gru/actor/id.hpp>
#include <gru/actor/raw.hpp>
#include <gru/actor/raw_factory.hpp>
#include <gru/shape/desc.hpp>
#include <gru/Filter.hpp>

namespace glutpp {
	namespace actor {
		class desc {
			public:
				friend class boost::serialization::access;
				desc();
				template<class Archive> void	save(Archive & ar, unsigned int const & version) const {
					ar << boost::serialization::make_nvp("i",i_);
					ar << boost::serialization::make_nvp("type",type_);
					
					ar << boost::serialization::make_nvp("raw",*raw_);
					
					ar << boost::serialization::make_nvp("actors",actors_);
					ar << boost::serialization::make_nvp("shapes",shapes_);
				}
				template<class Archive> void	load(Archive & ar, unsigned int const & version) {
					ar >> boost::serialization::make_nvp("i",i_);
					ar >> boost::serialization::make_nvp("type",type_);
					
					
					glutpp::master::Global()->actor_raw_factory_->reset(raw_, type_);

					ar >> boost::serialization::make_nvp("raw",*raw_);
					
					
					ar >> boost::serialization::make_nvp("actors",actors_);
					ar >> boost::serialization::make_nvp("shapes",shapes_);
				}
				
				
				// make this an archive...
				desc&		operator<<(boost::shared_ptr<glutpp::actor::actor> const & actor);

				
				BOOST_SERIALIZATION_SPLIT_MEMBER();
				
				void			load(boost::shared_ptr<glutpp::actor::actor>);
				//void			add_shape(glutpp::shape::desc);
				desc&			operator=(desc const &);
			public:
				int							i_;
				glutpp::actor::Type					type_;
				boost::shared_ptr<glutpp::actor::raw>			raw_;
				std::vector<boost::shared_ptr<glutpp::actor::desc> >	actors_;
				std::vector<boost::shared_ptr<glutpp::shape::desc> >	shapes_;


		};
	}
}

#endif








