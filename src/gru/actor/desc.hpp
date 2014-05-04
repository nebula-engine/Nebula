#ifndef __NEBULA_ACTOR_DESC_H__
#define __NEBULA_ACTOR_DESC_H__


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
#include <gru/Typed.hpp>

namespace glutpp {
	namespace actor {
		class desc {
			public:
				friend class boost::serialization::access;
				desc();
				virtual ~desc() {}
				template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("i",i_);
					ar & boost::serialization::make_nvp("type",type_);
					ar & boost::serialization::make_nvp("raw",raw_wrapper_);
					ar & boost::serialization::make_nvp("actors",actors_);
					ar & boost::serialization::make_nvp("shapes",shapes_);
				}
				
				// make this an archive...
				desc&		operator<<(boost::shared_ptr<glutpp::actor::actor> const & actor);

				void			load(boost::shared_ptr<glutpp::actor::actor>);
				//void			add_shape(glutpp::shape::desc);
				desc&			operator=(desc const &);

				boost::shared_ptr<glutpp::actor::raw>			getRaw();
			public:
				int							i_;
				glutpp::actor::Type					type_;
				//boost::shared_ptr<glutpp::actor::raw>			raw_;
				Neb::WrapperTyped<glutpp::actor::raw>			raw_wrapper_;
				std::vector<boost::shared_ptr<glutpp::actor::desc> >	actors_;
				std::vector<boost::shared_ptr<glutpp::shape::desc> >	shapes_;


		};
	}
}

#endif








