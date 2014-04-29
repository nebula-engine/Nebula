#ifndef __NEBULA_ACTOR_DESC_H__
#define __NEBULA_ACTOR_DESC_H__

//#include <math/transform.hpp>

//#include <galaxy/network/serial.hpp>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>


//#include <gru/actor/actor.hpp>
#include <gru/actor/id.hpp>
#include <gru/actor/raw.hpp>
#include <gru/shape/desc.hpp>
#include <gru/Filter.hpp>

namespace glutpp {
	namespace actor {

/*		typedef gal::network::vector_ext<glutpp::actor::desc> vec_actor_desc;
		typedef gal::network::vector_ext<glutpp::shape::desc> vec_shape_desc;
		typedef std::shared_ptr<vec_actor_desc> vec_actor_desc_s;
		typedef std::shared_ptr<vec_shape_desc> vec_shape_desc_s;

		typedef gal::network::serial_ext<id,raw,vec_actor_desc,vec_shape_desc>	ser_desc;
*/


		class desc {
			public:
				/*
				typedef std::shared_ptr<id>	ID_S;
				typedef std::shared_ptr<raw>	RAW_S;

				typedef glutpp::actor::desc		ACTOR_DESC;
				typedef glutpp::shape::desc		SHAPE_DESC;
				typedef std::shared_ptr<ACTOR_DESC>	ACTOR_DESC_S;
				typedef std::shared_ptr<SHAPE_DESC>	SHAPE_DESC_S;


				typedef gal::network::vector_ext<ACTOR_DESC>	VEC_ACTOR;
				typedef gal::network::vector_ext<SHAPE_DESC>	VEC_SHAPE;

				typedef std::shared_ptr<VEC_ACTOR>		VEC_ACTOR_S;
				typedef std::shared_ptr<VEC_SHAPE>		VEC_SHAPE_S;
*/

				desc();

				template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("i",i_);
					ar & boost::serialization::make_nvp("type",type_);
					
				       	raw_ = glutpp::master::Global()->actor_raw_factory_->create(type_);
					
					ar & boost::serialization::make_nvp("raw",raw_);
					
					ar & boost::serialization::make_nvp("actors",actors_);
					ar & boost::serialization::make_nvp("shapes",shapes_);
				}

				void			load(boost::shared_ptr<glutpp::actor::actor>);
				//void			add_shape(glutpp::shape::desc);



				desc&			operator=(desc const &);


				int							i_;
				glutpp::actor::Type					type_;
				boost::shared_ptr<glutpp::actor::raw>			raw_;
				std::vector<boost::shared_ptr<glutpp::actor::desc> >	actors_;
				std::vector<boost::shared_ptr<glutpp::shape::desc> >	shapes_;


		};
	}
}

#endif








