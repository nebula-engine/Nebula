#ifndef __GLUTPP_NETWORK_ACTOR_UPDATE_HPP__
#define __GLUTPP_NETWORK_ACTOR_UPDATE_HPP__

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <neb/core/scene/Util/Types.hh>

//#include <neb/config.hh> // gru/config.hpp.in
//#include <neb/master.hh>
//#include <neb/core/scene/desc.hh>
//#include <neb/core/actor/desc.hh>
//#include <neb/core/actor/event.hh>
#include <neb/core/actor/Util/Types.hh>

//#include <neb/core/scene/Base.hh>

#include <neb/message/Actor/Base.hh>

namespace neb {
	namespace message {
		namespace actor {
			struct Update:
				virtual public neb::message::actor::base
			{	
				Update() {}
			};
			class OUpdate:
				virtual public neb::message::actor::OBase,
				virtual public neb::message::actor::Update
			{
				public:
					/** @brief Save %Actor. */
					OUpdate&		operator<<(sp::shared_ptr<neb::core::actor::base> actor);

					virtual void		serialize(boost::archive::polymorphic_oarchive& ar, unsigned int const & version);

					::std::vector< sp::shared_ptr<neb::core::actor::base> >	actors_;
			};
			class IUpdate:
				virtual public neb::message::actor::IBase,
				virtual public neb::message::actor::Update
			{
				/** @brief Load */
				virtual void		serialize(boost::archive::polymorphic_iarchive& ar, unsigned int const & version);
			};
		}
	}
}

#endif



