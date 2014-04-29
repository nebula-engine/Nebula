#ifndef __GLUTPP_NETWORK_MESSAGE_H__
#define __GLUTPP_NETWORK_MESSAGE_H__

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <gru/config.hpp>
#include <gru/master.hpp>
#include <gru/scene/desc.hpp>
#include <gru/actor/desc.hpp>
#include <gru/actor/addr.hpp>
#include <gru/actor/event.hpp>
#include <gru/actor/raw_factory.hpp>


namespace glutpp {
	namespace network {
		namespace actor {

/*			typedef gal::network::vector_ext<
				glutpp::actor::raw,
				glutpp::actor::addr>
					vec_addr_raw;

			typedef std::shared_ptr<vec_addr_raw> vec_addr_raw_s;

			typedef gal::network::serial_ext<
				glutpp::actor::addr,
				glutpp::actor::desc>
					ser_create;

			typedef gal::network::serial_ext<vec_addr_raw> ser_update;
			
			typedef gal::network::serial_ext<
				glutpp::actor::addr,
				glutpp::actor::event>
					ser_event;

*/
			struct addr_raw {
				addr_raw() {}
				
				
				
				template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
					ar & addr_;
					ar & type_;
					
					raw_ = glutpp::master::Global()->actor_raw_factory_->create(type_);
					
					ar & *raw_;
				}
				
				glutpp::actor::addr			addr_; //() { return std::get<0>(ser_create::tup_); }
				glutpp::actor::Type			type_;
				boost::shared_ptr<glutpp::actor::raw>	raw_; //() { return std::get<1>(tup_); }
			};

			struct create {
				void	load(boost::shared_ptr<glutpp::actor::actor> actor);

				template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
					ar & addr_;
					ar & desc_;
				}
				
				glutpp::actor::addr	addr_; //() { return std::get<0>(ser_create::tup_); }
				glutpp::actor::desc	desc_; //() { return std::get<1>(tup_); }
			};

			struct update {
				//typedef vec_addr_raw::tuple tuple;
				
				void load(boost::shared_ptr<glutpp::actor::actor> actor);
			
				template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
					ar & vector_;
				}	

				std::vector<boost::shared_ptr<glutpp::network::actor::addr_raw> >	vector_;
			};

			struct event {

				template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
					ar & addr_;
					ar & event_;
				}

				glutpp::actor::addr		addr_; //() { return std::get<0>(tup_); }
				glutpp::actor::event		event_; //() { return std::get<1>(tup_); }
			};
		}
		namespace scene {
			struct create {
				void load(glutpp::scene::scene_s scene);
				
				template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
					ar & addr_;
					ar & desc_;
				}

				glutpp::scene::addr	addr_;
				glutpp::scene::desc	desc_;
			};
		}
	}
}

#endif



